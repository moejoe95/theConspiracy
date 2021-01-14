#include "headers/Entity.hpp"
#include "headers/SoundManager.hpp"
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

void Entity::gravity() {

	int fallingSpeed = 5;
	boundingBox.y += fallingSpeed;
	intersection = collisionManager->checkCollision(this, boundingBox);
	if (intersection.h > 0) {
		boundingBox.y -= fallingSpeed;
		movement.down = false;
	} else {
		currentTexture = jumpTexture;
	}
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

	boundingBox.x += step;

	// collision avoidance
	SDL_Rect new_intersection = collisionManager->checkCollision(this, boundingBox);
	if (new_intersection.w > intersection.w) {
		boundingBox.x -= step;
	}

	currentWalkIdx = currentWalkIdx >= walkAnimSize - 1 ? 0 : currentWalkIdx + 1;

	currentTexture = walkTextures.at(currentWalkIdx);
}

void Entity::renderShoot() {
	if (!startShoot && currentShootIdx == 0)
		return;

	if (currentShootIdx == 0)
		SoundManager::getInstance().playGunSound();

	currentShootIdx++;
	if (currentShootIdx >= shootAnimSize - 1) {
		// create bullet
		int x = boundingBox.x - 10; // offset to not walk into own bullet
		if (flip == SDL_FLIP_NONE)
			x += boundingBox.w + 10;

		int y = boundingBox.y + boundingBox.h / 2;

		if (ammo > 0) {
			firedBullets.emplace_back(x, y, flip, renderer, bulletTexture);
			ammo--;
		} else
			ammo = 0;

		startShoot = false;
		currentShootIdx = 0;
	}
	currentTexture = shootTextures.at(currentShootIdx);
}

void Entity::renderBullets() {

	std::vector<Bullet> newBullets;
	for (auto &bullet : firedBullets) {
		collisionManager->deregisterObject(&bullet);
		bullet.render();
		if (!bullet.isOutOfSight()) {
			newBullets.push_back(bullet);
		}
	}

	firedBullets = newBullets;

	for (auto &bullet : firedBullets) {
		collisionManager->registerObject(&bullet);
	}
}

void Entity::renderHurt() {
	if (currentHurtIdx >= 0) {
		currentTexture = hurtTextures[currentHurtIdx++];
		if (currentHurtIdx >= hurtAnimSize) {
			currentHurtIdx = -1;
		}
	}

	if (currentHurtIdx == 1)
		SoundManager::getInstance().playHurtSound();
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

void Entity::reset(std::array<int, 2> position) {
	life = 100;
	ammo = 20;
	boundingBox.x = position[0];
	boundingBox.y = position[1];
}
