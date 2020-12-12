#ifndef GAME_HPP
#define GAME_HPP

#include "CollisionManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "RenderObject.hpp"
#include "Room.hpp"
#include <SDL.h>
#include <functional>
#include <string>
#include <vector>

class Game {

  public:
	Game(const std::string &roomName, SDL_Renderer *renderer);

	bool renderGame();

  private:
	SDL_Renderer *renderer;
	CollisionManager collisionManager;
	Room room;
	Player player;
	std::vector<Enemy> enemies;
};

#endif // GAME_HPP
