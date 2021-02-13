#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Bullet.hpp"
#include "CollisionManager.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "Room.hpp"
#include <SDL.h>
#include <array>
#include <functional>
#include <map>
#include <string>
#include <vector>

const int STEP_SIZE = 4;

class Entity : public RenderObject {

  public:
	void moveRight();
	void stopMoveRight();
	void moveLeft();
	void stopMoveLeft();
	void shoot();
	void demage(int damage) override;
	bool visible() override;
	void reset(std::array<int, 2> position);
	bool isAlive = true;

  protected:
	struct Movement {
		bool right = false;
		bool left = false;
		bool up = false;
		bool down = false;
	} movement;

	bool startShoot = false;

	// TODO make "actions" class
	int currentWalkIdx = 0;
	int currentShootIdx = 0;
	int currentHurtIdx = -1;
	int currentDieIdx = -1;
	int startHeight = 0;
	int stepSize = 0;
	int walkAnimSize = 0;
	int shootAnimSize = 0;
	int dieAnimSize = 0;
	int hurtAnimSize = 0;

	int life = 100;
	int ammo = 20;

	bool drawBoundingBox;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect boundingBox;
	SDL_Rect intersection;
	SDL_Texture *currentTexture;
	SDL_Texture *idleTexture;
	SDL_Texture *bulletTexture;
	SDL_Texture *jumpTexture;
	std::vector<SDL_Texture *> walkTextures;
	std::vector<SDL_Texture *> shootTextures;
	std::vector<SDL_Texture *> hurtTextures;
	std::vector<SDL_Texture *> dieTextures;

	std::vector<Bullet> firedBullets;

	void gravity();
	void renderMove();

	const std::vector<SDL_Rect> getBoundingBoxes() override;
	void renderShoot();
	void renderBullets();

	void renderHurt();
	void renderDie();

	virtual void render() = 0;
};

#endif // ENTITY_HPP
