#include "Bullet.hpp"
#include "Game.hpp"
#include "utils/Constants.hpp"
#include "utils/Utils.hpp"
#include <SDL.h>
#include <spdlog/spdlog.h>

int Bullet::count = 0;

Bullet::Bullet(int x, int y, SDL_RendererFlip flip, SDL_Texture *texture, bool granade)
    : flip(flip), texture(texture), isGranade(granade) {

	id = "bullet_" + std::to_string(count++);

	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = BULLET_WIDTH;
	boundingBox.h = BULLET_HEIGHT;

	if (granade) {
		boundingBox.w = GRANADE_WIDTH;
		boundingBox.h = GRANADE_HEIGHT;
	}

	std::string explodePath = getResourcePath("bullet/blast");
	for (int i = 0; i <= BULLET_BLAST_ANIM_SIZE; i++) {
		explodeTextures.push_back(game().getRenderer().loadTexture(explodePath + std::to_string(i + 1) + PNG));
	}

	spdlog::debug(id + " constructed");
}

void Bullet::render() {

	if (explodeIdx < 0) {
		if (flip == SDL_FLIP_NONE && !onFloor)
			boundingBox.x += BULLET_VELOCITY;
		else if (!onFloor)
			boundingBox.x -= BULLET_VELOCITY;

		if (boundingBox.x > SCREEN_WIDTH * 2 || boundingBox.x < 0) {
			outOfSight = true;
			spdlog::debug(id + " of of sight");
		}

		if (isGranade) {
			SDL_Rect intersection = game().getCollisionManager().checkCollision(this, boundingBox);
			if (intersection.h > 0)
				onFloor = true;

			if (!onFloor)
				boundingBox.y += 5;
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
