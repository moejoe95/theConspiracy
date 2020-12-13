#include "headers/Bullet.hpp"
#include "headers/Constants.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>

int Bullet::count = 0;

Bullet::Bullet(int x, int y, SDL_RendererFlip flip, SDL_Renderer *renderer, SDL_Texture *texture,
               CollisionManager *collisionManager)
    : flip(flip), renderer(renderer), texture(texture), collisionManager(collisionManager) {

	id = "bullet_" + std::to_string(count++);

	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = BULLET_WIDTH;
	boundingBox.h = BULLET_HEIGHT;

	std::string explodePath = getResourcePath("bullet/blast");
	for (int i = 0; i <= BULLET_BLAST_ANIM_SIZE; i++) {
		explodeTextures.push_back(loadTexture(explodePath + std::to_string(i + 1) + PNG, renderer));
	}

	spdlog::debug(id + " constructed");
}

void Bullet::render() {

	if (explodeIdx < 0) {
		if (flip == SDL_FLIP_NONE)
			boundingBox.x += BULLET_VELOCITY;
		else
			boundingBox.x -= BULLET_VELOCITY;

		if (boundingBox.x > SCREEN_WIDTH || boundingBox.x < 0) {
			outOfSight = true;
			collisionManager->deregisterObject(this);
			spdlog::debug("bullet of of sight");
			return;
		}

		renderTexture(texture, renderer, boundingBox, flip);
	}

	collisionManager->registerObject(this);

	if (explodeIdx >= 0 && !outOfSight) {
		explodeIdx++;
		boundingBox.w = BULLET_BLAST_SIZE;
		boundingBox.h = BULLET_BLAST_SIZE;
		renderTexture(explodeTextures[explodeIdx], renderer, boundingBox);
		if (explodeIdx >= BULLET_BLAST_ANIM_SIZE) {
			collisionManager->deregisterObject(this);
			outOfSight = true;
		}
	}
}

const std::vector<SDL_Rect> Bullet::getBoundingBoxes() {
	std::vector<SDL_Rect> boundingBoxes;
	boundingBoxes.push_back(boundingBox);
	return boundingBoxes;
}

void Bullet::demage(int demage) {
	// start explosion
	if (explodeIdx < 0)
		explodeIdx = 0;
}

int Bullet::demageValue() {
	return 1;
}

bool Bullet::isOutOfSight() {
	return outOfSight;
}
