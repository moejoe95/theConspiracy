
#include "headers/Game.hpp"
#include "headers/Bullet.hpp"
#include "headers/Constants.hpp"
#include "headers/EventDispatcher.hpp"
#include "headers/Player.hpp"
#include "headers/Room.hpp"
#include "headers/SDLException.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <iostream>

Game::Game(const std::string &roomName, SDL_Renderer *renderer)
    : renderer(renderer), collisionManager(renderer), room(roomName, renderer, &collisionManager),
      player(room.playerStart, renderer, &collisionManager) {

	enemies.emplace_back(room.enemyStart, renderer, &collisionManager);
	spdlog::info("new game initalized");
}

bool Game::renderGame() {

	if (SDL_QUIT == dispatchKeyEvent(player))
		return false;

	room.render();

	player.render();
	if (!player.isAlive) {
		spdlog::info("game over - player died");
		return false;
	}
	/*
	    std::vector<Enemy> new_enemies;
	    for (auto &enemy : enemies) {
	        enemy.render();
	        if (enemy.isAlive) {
	            new_enemies.push_back(enemy);
	        }
	    }
	    enemies = new_enemies;
*/

	// draw life information
	if (getArg<bool>("showStatus")) {
		std::string text = "Life: " + std::to_string(player.getLife());
		renderText(text, renderer, 0, 0);

		text = "Ammo: " + std::to_string(player.getAmmo());
		renderText(text, renderer, 0, 20);
	}

	return true;
}
