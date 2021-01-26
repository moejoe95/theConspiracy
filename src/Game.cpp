
#include "headers/Game.hpp"
#include "cereal/archives/json.hpp"
#include "headers/Bullet.hpp"
#include "headers/Constants.hpp"
#include "headers/Player.hpp"
#include "headers/Room.hpp"
#include "headers/SDLException.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <filesystem>
#include <functional>
#include <iostream>
#include <vector>

Game::Game(const std::string &roomName, Renderer *renderer)
    : renderer(renderer), collisionManager(), room(roomName, renderer, &collisionManager),
      player(room.playerStart, renderer, &collisionManager), roomName(roomName) {

	enemies.emplace_back(room.enemyStart, renderer, &collisionManager);
	spdlog::info("new game initalized");
}

void Game::reset() {
	player.reset(room.playerStart);
	for (auto &enemy : enemies) {
		enemy.revive();
	}
	// delete serialized objects if new game
	if (std::filesystem::exists("data/player.json")) {
		std::filesystem::remove("data/player.json");
	}
}

void Game::reload() {
	spdlog::debug("load player");
	if (std::filesystem::exists("data/player.json")) {
		std::ifstream is("data/player.json");
		cereal::JSONInputArchive iarchive(is);
		iarchive(player);
	}

	// reload correct room
}

bool Game::renderGame() {

	int button = dispatchEvents();

	if (button >= 0 || showMenu) {
		renderer->drawMenu();
		if (button < 1) { // continue
			return true;
		}
		if (button == 1) { // new game
			reset();
		} else if (button == 2) // exit game
			return false;
	}

	if (button < 1 && gameStart) {
		reload();
		gameStart = false;
	} else if (button == 1) {
		gameStart = false;
		room.resetSavePoint();
	}

	if (!player.isAlive) {
		renderer->drawGameOverScreen();
		gameOverSreenTime--;
		if (gameOverSreenTime < 0) {
			showMenu = true;
			gameOverSreenTime = 50;
		}
		return true;
	}

	// render
	room.render();
	player.render();
	for (auto &enemy : enemies) {
		enemy.render();
	}

	if (player.getPosition().x > SCREEN_WIDTH) {
		renderer->setXOffset(-SCREEN_WIDTH);
	} else if (player.getPosition().x < SCREEN_WIDTH) {
		renderer->setXOffset(0);
	}

	if (room.checkSavePoint(player.getPosition().x)) {
		spdlog::debug("serialize player");
		std::ofstream os("data/player.json");
		cereal::JSONOutputArchive oarchive(os);
		oarchive(player);
	}

	if (room.isOnGoal(player.getPosition().x)) {
		room.nextRoom();
		player.resetPosition(room.playerStart);
		spdlog::debug("player on goal");
	}

	// draw life information
	if (getArg<bool>("showStatus")) {
		std::string text = "Life: " + std::to_string(player.getLife());
		renderer->drawText(text, 0, 0);

		text = "Ammo: " + std::to_string(player.getAmmo());
		renderer->drawText(text, 0, 20);
	}

	return true;
}

int Game::dispatchEvents() {
	int keyCode = -1;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_KEYDOWN: {
			auto key = event.key.keysym.sym;
			if (player.keyDownEventMap.find(key) != player.keyDownEventMap.end()) {
				player.keyDownEventMap.find(key)->second();
			} else if (key == SDLK_q || key == SDLK_ESCAPE) {
				showMenu = true;
			}
		} break;

		case SDL_KEYUP: {
			auto key = event.key.keysym.sym;
			if (player.keyUpEventMap.find(key) != player.keyUpEventMap.end()) {
				player.keyUpEventMap.find(key)->second();
			}
		} break;
		case SDL_MOUSEBUTTONDOWN:
			if (showMenu) {
				std::vector<SDL_Rect> buttons = renderer->drawMenu();
				SDL_Point mouse;
				SDL_GetMouseState(&mouse.x, &mouse.y);
				for (int i = 0; i < buttons.size(); i++) {
					const SDL_Point constMouse = mouse;
					if (SDL_PointInRect(&constMouse, &buttons[i])) {
						keyCode = i;
						showMenu = false;
					}
				}
			}
			break;
		}
	}
	return keyCode;
}
