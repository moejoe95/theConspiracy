#ifndef GAME_HPP
#define GAME_HPP

#include "managers/CollisionManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "Room.hpp"
#include <SDL.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Game {

  public:
	Game();

	bool renderGame();

	void renderClear();

	void renderUpdate();

	Renderer &getRenderer();

	CollisionManager &getCollisionManager();

  private:
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<CollisionManager> collisionManager;
	std::unique_ptr<Room> room;
	std::unique_ptr<Player> player;

	std::vector<Enemy> enemies;
	bool showMenu = true;
	bool gameStart = true;
	int gameOverSreenTime = 50;

	int dispatchEvents();
	void reload();
	void reset();
	void deleteState();
};

Game &game();

#endif // GAME_HPP
