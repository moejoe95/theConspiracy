#include "headers/Enemy.hpp"
#include "headers/Constants.hpp"
#include "headers/Game.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <functional>
#include <iostream>

int Enemy::count = 0;

Enemy::Enemy(std::array<int, 2> position) {

	id = "enemy_" + std::to_string(count++);

	boundingBox.x = position[0];
	boundingBox.y = position[1];
	boundingBox.w = ENEMY_WIDTH;
	boundingBox.h = ENEMY_HEIGTH;

	game().getCollisionManager().registerObject(this);

	stepSize = 4;
	walkAnimSize = 9;
	shootAnimSize = 5;
	hurtAnimSize = 6;
	dieAnimSize = 6;

	drawBoundingBox = getArg<bool>("drawBoundingBox");
	spdlog::info(drawBoundingBox);

	loadTextures();

	spdlog::info(id + " initalized");

	movement.left = true;
}

void Enemy::loadTextures() {

	std::string walkPath = getResourcePath("enemy/walk");
	for (int i = 0; i < ENEMY_WALK_ANIM_SIZE; i++) {
		walkTextures.push_back(game().getRenderer().loadTexture(walkPath + std::to_string(i + 1) + PNG));
	}

	std::string shootPath = getResourcePath("enemy/shoot");
	for (int i = 0; i < ENEMY_SHOOT_ANIM_SIZE; i++) {
		shootTextures.push_back(game().getRenderer().loadTexture(shootPath + std::to_string(i + 1) + PNG));
	}

	std::string hurtPath = getResourcePath("enemy/hurt");
	for (int i = 0; i < hurtAnimSize; i++) {
		hurtTextures.push_back(game().getRenderer().loadTexture(hurtPath + std::to_string(i + 1) + PNG));
	}

	std::string diePath = getResourcePath("enemy/die");
	for (int i = 0; i < dieAnimSize; i++) {
		dieTextures.push_back(game().getRenderer().loadTexture(diePath + std::to_string(i + 1) + PNG));
	}

	bulletTexture = game().getRenderer().loadTexture(getResourcePath("bullet") + "bullet.png");

	idleTexture = game().getRenderer().loadTexture(getResourcePath() + "enemy/idle.png");
	jumpTexture = idleTexture;

	spdlog::info("enemy textures loaded");
}

void Enemy::walk() {

	if (steps == 3) {
		bool switchDir = movement.left;
		movement.left = movement.right;
		movement.right = switchDir;
		steps = 0;
		sleep = 50;
	}

	renderMove();
	if (currentWalkIdx <= 0) {
		steps++;
	}
}

void Enemy::render() {

	if (!isAlive) {
		isVisible = false;
		return;
	}

	currentTexture = idleTexture;
	game().getCollisionManager().registerObject(this);
	intersection = game().getCollisionManager().checkCollision(this, boundingBox);

	if (sleep <= 0) {
		walk();
	}
	if (sleep == 25) {
		startShoot = true;
	}
	sleep--;

	renderShoot();
	gravity();
	renderHurt();
	renderDie();

	game().getRenderer().drawTexture(currentTexture, boundingBox, flip);

	if (drawBoundingBox) {
		const SDL_Rect playerBB = boundingBox;
		game().getRenderer().drawRect(playerBB);
	}

	renderBullets();
}

void Enemy::revive() {
	isAlive = true;
	life = 100;
	isVisible = true;
}

bool Enemy::visible() {
	return isVisible;
}

int Enemy::demageValue() {
	return 5;
}

Enemy::~Enemy() {
	/*
	SDL_DestroyTexture(idleTexture);
	SDL_DestroyTexture(bulletTexture);
	for (auto tex : walkTextures)
	    SDL_DestroyTexture(tex);
	for (auto tex : shootTextures)
	    SDL_DestroyTexture(tex);
	for (auto tex : hurtTextures)
	    SDL_DestroyTexture(tex);
	for (auto tex : dieTextures)
	    SDL_DestroyTexture(tex);
	    */
}
