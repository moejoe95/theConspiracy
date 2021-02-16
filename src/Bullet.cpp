#include "Bullet.hpp"
#include "utils/Constants.hpp"
#include "Game.hpp"
#include "utils/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>

int Bullet::count = 0;

Bullet::Bullet(int x, int y, SDL_RendererFlip flip, SDL_Texture *texture) : flip(flip), texture(texture) {

	id = "bullet_" + std::to_string(count++);

	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = BULLET_WIDTH;
	boundingBox.h = BULLET_HEIGHT;

	std::string explodePath = getResourcePath("bullet/blast");
	for (int i = 0; i <= BULLET_BLAST_ANIM_SIZE; i++) {
		explodeTextures.push_back(game().getRenderer().loadTexture(explodePath + std::to_string(i + 1) + PNG));
	}

	spdlog::debug(id + " constructed");
}

void Bullet::render() {

	if (explodeIdx < 0) {
		if (flip == SDL_FLIP_NONE)
			boundingBox.x += BULLET_VELOCITY;
		else
			boundingBox.x -= BULLET_VELOCITY;

		if (boundingBox.x > SCREEN_WIDTH * 2 || boundingBox.x < 0) {
			outOfSight = true;
			spdlog::debug(id + " of of sight");
		}

		game().getRenderer().drawTexture(texture, boundingBox, flip);
	}

	if (explodeIdx >= 0) {
		explodeIdx++;
		boundingBox.w = BULLET_BLAST_SIZE;
		boundingBox.h = BULLET_BLAST_SIZE;
		game().getRenderer().drawTexture(explodeTextures[explodeIdx], boundingBox);
		if (explodeIdx >= BULLET_BLAST_ANIM_SIZE) {
			outOfSight = true;
			spdlog::debug(id + " exploded");
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

bool Bullet::visible() {
	return !outOfSight;
}

int Bullet::demageValue() {
	return 1;
}

bool Bullet::isOutOfSight() {
	return outOfSight;
}
