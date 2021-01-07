#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "CollisionManager.hpp"
#include "Entity.hpp"
#include "Renderer.hpp"
#include <SDL.h>

const int ENEMY_WIDTH = 110;
const int ENEMY_HEIGTH = 110;
const int ENEMY_WALK_ANIM_SIZE = 9;
const int ENEMY_STEP_SIZE = 4;
const int ENEMY_JUMP_ANIM_SIZE = 10;
const int ENEMY_SHOOT_ANIM_SIZE = 5;

class Enemy : public Entity {

  public:
	Enemy(std::array<int, 2> position, Renderer *renderer, CollisionManager *collisionManager);
	~Enemy();

	void render() override;
	int demageValue() override;
	int steps = 0;
	int sleep = 0;
	static int count;

  private:
	void jump();
	void loadTextures();
	void walk();
};

#endif // ENEMY_HPP