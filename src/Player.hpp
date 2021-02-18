#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../include/cereal/types/base_class.hpp"
#include "Entity.hpp"
#include "managers/CollisionManager.hpp"
#include "managers/Renderer.hpp"
#include <SDL.h>
#include <map>
#include <string>

const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGTH = 100;
const int PLAYER_JUMP_SIZE = 20;
const int PLAYER_JUMP_HEIGHT = 120;

class Player : public Entity {

  public:
	Player(std::array<int, 2> position);
	~Player();

	std::map<SDL_Keycode, std::function<void()>> keyUpEventMap;
	std::map<SDL_Keycode, std::function<void()>> keyDownEventMap;

	void render() override;
	int demageValue() override;
	void demage(int demage) override;
	int getLife();
	int getAmmo();
	void addAmmo(int ammo);
	void addLife(int life);
	SDL_Rect getPosition();
	void resetPosition(std::array<int, 2> position);

	// serializing
	template <class Archive>
	void serialize(Archive &archive) {
		archive(life, ammo, boundingBox.x, boundingBox.y);
	}

	void save();
	void load();
	void remove();

  private:
	void jump();
	void loadTextures();
	void renderJump();

	bool godMode;
};

#endif // PLAYER_HPP
