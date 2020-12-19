#include "headers/Entity.hpp"
#include "spdlog/spdlog.h"

void Entity::moveLeft() {
	movement.left = true;
}

void Entity::stopMoveLeft() {
	movement.left = false;
}

void Entity::moveRight() {
	movement.right = true;
}

void Entity::stopMoveRight() {
	movement.right = false;
}

void Entity::shoot() {
	startShoot = true;
}

const std::vector<SDL_Rect> Entity::getBoundingBoxes() {
	std::vector<SDL_Rect> boundingBoxes;
	boundingBoxes.push_back(boundingBox);
	return boundingBoxes;
}

bool Entity::gravity(int offset) {

	int fallingSpeed = 5;
	boundingBox.y += fallingSpeed;
	intersection = collisionManager->checkCollision(this, boundingBox);
	if (intersection.h > 0) {
		boundingBox.y -= fallingSpeed;
		return true;
	}
	currentTexture = jumpTexture;

	return false;
}

void Entity::renderMove() {
	int step;
	if (movement.right) {
		step = stepSize;
		flip = SDL_FLIP_NONE;
	} else if (movement.left) {
		step = -stepSize;
		flip = SDL_FLIP_HORIZONTAL;
	} else
		return;

	int old_x = intersection.x;
	boundingBox.x += step;
	intersection = collisionManager->checkCollision(this, boundingBox);
	if (intersection.x > old_x)
		boundingBox.x -= step;

	currentWalkIdx = currentWalkIdx >= walkAnimSize - 1 ? 0 : currentWalkIdx + 1;

	currentTexture = walkTextures.at(currentWalkIdx);
}

void Entity::renderShoot() {
	if (!startShoot && currentShootIdx == 0)
		return;

	currentShootIdx++;
	if (currentShootIdx >= shootAnimSize - 1) {
		// create bullet
		int x = boundingBox.x;
		if (flip == SDL_FLIP_NONE)
			x += boundingBox.w;

		int y = boundingBox.y + boundingBox.h / 2;

		firedBullets.emplace_back(x, y, flip, renderer, bulletTexture, collisionManager);

		startShoot = false;
		currentShootIdx = 0;
	}
	currentTexture = shootTextures.at(currentShootIdx);
}

void Entity::renderBullets() {
	// delete bullets out of map because location of bullets may have changed
	// (due to newly inserted bullets)
	std::vector<std::string> ids;
	for (auto &bullet : firedBullets) {
		ids.push_back(bullet.getId());
	}
	collisionManager->cleanBullets(ids);

	std::vector<Bullet> newBullets;
	for (auto &bullet : firedBullets) {
		bullet.render();
		if (!bullet.isOutOfSight())
			newBullets.push_back(bullet);
	}
	firedBullets = newBullets;
}

void Entity::renderHurt() {
	if (currentHurtIdx >= 0) {
		currentTexture = hurtTextures[currentHurtIdx++];
		if (currentHurtIdx >= hurtAnimSize) {
			currentHurtIdx = -1;
		}
	}
}

void Entity::renderDie() {
	if (currentDieIdx >= 0) {
		currentTexture = dieTextures[currentDieIdx++];
		if (currentDieIdx >= dieAnimSize) {
			currentDieIdx = -1;
			isAlive = false;
			collisionManager->deregisterObject(this);
		}
	}
}

void Entity::demage(int demage) {
	life -= demage;
	if (life <= 0 && currentDieIdx < 0) {
		currentDieIdx = 0;
		currentHurtIdx = -1;
		return;
	} else if (currentHurtIdx < 0) {
		currentHurtIdx = 0;
	}
}
