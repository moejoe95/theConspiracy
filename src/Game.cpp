
#include "Game.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "managers/SoundManager.hpp"
#include "utils/Constants.hpp"
#include "utils/SDLException.hpp"
#include "utils/Utils.hpp"
#include <SDL.h>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <vector>

static Game *instance;

Game &game() {
	if (!instance) {
		spdlog::error("game not initialized");
	}
	return *instance;
}

Game::Game()
    : renderer(std::make_unique<Renderer>()), collisionManager(std::make_unique<CollisionManager>()),
      soundManager(std::make_unique<SoundManager>()) {

	instance = this;

	room = std::make_unique<Room>();
	player = std::make_unique<Player>(room.get()->playerStart);

	initEnemies();

	// play backround
	soundManager.get()->playBackgroundSound();

	spdlog::info("new game initalized");
}

Renderer &Game::getRenderer() {
	return *renderer;
}

CollisionManager &Game::getCollisionManager() {
	return *collisionManager;
}

SoundManager &Game::getSoundManager() {
	return *soundManager;
}

void Game::renderGame() {

	int button = dispatchEvents();
	if (showMenu) {
		menu(button);
		return;
	}

	if (!player.get()->isAlive) {
		renderGameOver();
		return;
	}

	// render
	room.get()->render();
	player.get()->render();
	for (auto &enemy : enemies) {
		enemy.render();
	}
	renderStatus();

	if (player.get()->getPosition().x > SCREEN_WIDTH) {
		renderer->setXOffset(-SCREEN_WIDTH);
	} else if (player.get()->getPosition().x < SCREEN_WIDTH) {
		renderer->setXOffset(0);
	}

	checkOnSavePoint();
	checkOnGoal();
}

void Game::menu(int button) {

	renderer->drawMenu();

	if (button == -1) {
		return;
	} else if (button == 1) { // new game
		reset();
	} else if (button == 2) { // exit game
		exit = true;
		return;
	}

	showMenu = false;

	if (button < 1 && gameStart) {
		reload();
		gameStart = false;
	} else if (button == 1) {
		gameStart = false;
		room.get()->resetSavePoint();
	}
}

void Game::renderStatus() {
	// draw status info on screen
	if (getArg<bool>("showStatus")) {
		std::string text = "Life: " + std::to_string(player.get()->getLife());
		renderer->drawText(text, 0, 0);

		text = "Ammo: " + std::to_string(player.get()->getAmmo());
		renderer->drawText(text, 0, 20);
	}
}

void Game::renderGameOver() {
	renderer->drawGameOverScreen();
	gameOverSreenTime--;
	if (gameOverSreenTime < 0) {
		showMenu = true;
		gameOverSreenTime = 50;
		if (!success)
			soundManager.get()->playGameOverSound();
	}
}

void Game::checkOnSavePoint() {
	if (room.get()->checkSavePoint(player.get()->getPosition().x)) {
		player.get()->save();
		room.get()->save();
	}
}

void Game::checkOnGoal() {
	if (room.get()->isOnGoal(player.get()->getPosition().x)) {
		bool gameOver = room.get()->nextRoom();
		if (gameOver) {
			soundManager.get()->playWinSound();
			soundManager.get()->playBackgroundSound();
			success = true;
			deleteState();
			player.get()->isAlive = false;
		}
		player.get()->resetPosition(room.get()->playerStart);
		initEnemies();
	}
}

void Game::initEnemies() {
	enemies.clear();
	enemies.reserve(room.get()->getEnemyPositions().size() + 1);
	for (auto enemyPos : room.get()->getEnemyPositions()) {
		enemies.emplace_back(enemyPos, false);
	}
	if (room.get()->hasBoss())
		enemies.emplace_back(room.get()->getBossPosition(), true);
}

void Game::reset() {
	player.get()->reset(room.get()->playerStart);
	room.get()->reset();
	initEnemies();
	deleteState();
}

void Game::deleteState() {
	player.get()->remove();
	room.get()->remove();
}

void Game::reload() {
	player.get()->load();
	room.get()->load();
	if (room.get()->getCurrentMapIdx() > 1)
		room.get()->parseMap();
	initEnemies();
}

void Game::renderClear() {
	renderer->clear();
}

void Game::renderUpdate() {
	renderer->update();
}

bool Game::isExit() {
	return exit;
}

int Game::dispatchEvents() {
	int keyCode = -1;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_KEYDOWN: {
			auto key = event.key.keysym.sym;
			if (player.get()->keyDownEventMap.find(key) != player.get()->keyDownEventMap.end()) {
				player.get()->keyDownEventMap.find(key)->second();
			} else if (key == SDLK_q || key == SDLK_ESCAPE) {
				showMenu = true;
			}
		} break;

		case SDL_KEYUP: {
			auto key = event.key.keysym.sym;
			if (player.get()->keyUpEventMap.find(key) != player.get()->keyUpEventMap.end()) {
				player.get()->keyUpEventMap.find(key)->second();
			}
		} break;
		case SDL_MOUSEBUTTONDOWN:
			if (showMenu) {
				std::vector<SDL_Rect> buttons = renderer->drawMenu();
				SDL_Point mouse;
				SDL_GetMouseState(&mouse.x, &mouse.y);
				int i = 0;
				for (auto it = buttons.begin(); it != buttons.end(); ++it) {
					const SDL_Point constMouse = mouse;
					if (SDL_PointInRect(&constMouse, &buttons[i])) {
						keyCode = i;
					}
					++i;
				}
			}
			break;
		}
	}
	return keyCode;
}
