#ifndef GAME_HPP
#define GAME_HPP

#include "CollisionManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "Room.hpp"
#include <SDL.h>
#include <functional>
#include <string>
#include <vector>

class Game {

  public:
	explicit Game(Renderer *renderer);

	bool renderGame();

  private:
	Renderer *renderer;
	CollisionManager collisionManager;
	Room room;
	Player player;
	std::vector<Enemy> enemies;
	bool showMenu = true;
	bool gameStart = true;
	int gameOverSreenTime = 50;

	int dispatchEvents();
	void reload();
	void reset();
	void deleteState();
};

#endif // GAME_HPP
