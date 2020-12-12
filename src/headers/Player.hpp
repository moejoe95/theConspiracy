#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CollisionManager.hpp"
#include "Entity.hpp"
#include <SDL.h>
#include <map>
#include <string>

const int PLAYER_WIDTH = 160;
const int PLAYER_HEIGTH = 120;
const int PLAYER_JUMP_SIZE = 20;
const int PLAYER_JUMP_HEIGHT = 120;

class Player : public Entity {

  public:
	Player(std::array<int, 2> position, SDL_Renderer *renderer, CollisionManager *collisionManager);
	~Player();

	std::map<SDL_Keycode, std::function<void()>> keyUpEventMap;
	std::map<SDL_Keycode, std::function<void()>> keyDownEventMap;

	void render() override;
	int demageValue() override;
	int getLife();

  private:
	void jump();
	void loadTextures();
	void renderJump();
};

#endif // PLAYER_HPP
