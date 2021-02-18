#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "managers/CollisionManager.hpp"
#include "managers/Renderer.hpp"
#include <SDL.h>
#include <random>
#include <vector>

const int ENEMY_WIDTH = 110;
const int ENEMY_HEIGTH = 110;

class Enemy : public Entity {

  public:
	Enemy(std::array<int, 2> position, bool isBoss);
	~Enemy();

	void render() override;
	int demageValue() override;
	bool visible() override;
	void renderHurt();
	void revive();

	int steps = 0;
	int sleep = 0;
	static int count;

  private:
	void jump();
	void loadTextures();
	void walk();
	void renderGranadeThrow();
	void renderGranade();

	bool isVisible = true;
	bool isBoss = false;

	int granadeAnimSize = 0;
	int currentGranadeIdx = -1;
	std::vector<SDL_Texture *> granadeThrowTextures;
	SDL_Texture *granadeTexture;
};

#endif // ENEMY_HPP