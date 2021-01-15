#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../cereal/types/base_class.hpp"
#include "CollisionManager.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"
#include <SDL.h>
#include <map>
#include <string>

const int PLAYER_WIDTH = 160;
const int PLAYER_HEIGTH = 120;
const int PLAYER_JUMP_SIZE = 20;
const int PLAYER_JUMP_HEIGHT = 120;

class Player : public Entity {

  public:
	Player(std::array<int, 2> position, Renderer *renderer, CollisionManager *collisionManager);
	~Player();

	std::map<SDL_Keycode, std::function<void()>> keyUpEventMap;
	std::map<SDL_Keycode, std::function<void()>> keyDownEventMap;

	void render() override;
	int demageValue() override;
	void demage(int demage) override;
	int getLife();
	int getAmmo();
	SDL_Rect getPosition();
	void resetPosition(std::array<int, 2> position);

	template <class Archive>
	void serialize(Archive &archive) {
		archive(life, ammo, boundingBox.x, boundingBox.y);
	}

  private:
	void jump();
	void loadTextures();
	void renderJump();

	bool godMode;
};

#endif // PLAYER_HPP
