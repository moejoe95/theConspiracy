#ifndef GAME_HPP
#define GAME_HPP

#include "Enemy.hpp"
#include "Player.hpp"
#include "RenderObject.hpp"
#include "Room.hpp"
#include "managers/CollisionManager.hpp"
#include "managers/Renderer.hpp"
#include "managers/SoundManager.hpp"
#include <SDL.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Game {

  public:
	Game();

	void renderGame();
	bool isExit();
	void renderClear();
	void renderUpdate();

	Renderer &getRenderer();
	CollisionManager &getCollisionManager();
	SoundManager &getSoundManager();

  private:
	int dispatchEvents();
	void reload();
	void reset();
	void deleteState();
	void initEnemies();
	void menu(int button);

	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<CollisionManager> collisionManager;
	std::unique_ptr<SoundManager> soundManager;
	std::unique_ptr<Room> room;
	std::unique_ptr<Player> player;

	std::vector<Enemy> enemies;

	bool showMenu = true;
	bool gameStart = true;
	bool exit = false;
	bool success = false;
	int gameOverSreenTime = 50;
};

Game &game();

#endif // GAME_HPP
