#include "Enemy.hpp"
#include "Game.hpp"
#include "utils/Constants.hpp"
#include "utils/Utils.hpp"
#include <SDL.h>
#include <spdlog/spdlog.h>

int Enemy::count = 0;

Enemy::Enemy(std::array<int, 2> position, bool isBoss) : isBoss(isBoss) {

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
	granadeAnimSize = 16;
	ammo = 100;

	if (isBoss)
		life = 200;

	drawBoundingBox = getArg<bool>("drawBoundingBox");
	spdlog::info(drawBoundingBox);

	loadTextures();
	movement.left = true;
}

void Enemy::loadTextures() {

	std::string walkPath = getResourcePath("enemy/walk");
	for (int i = 0; i < walkAnimSize; i++) {
		walkTextures.push_back(game().getRenderer().loadTexture(walkPath + std::to_string(i + 1) + PNG));
	}

	std::string shootPath = getResourcePath("enemy/shoot");
	for (int i = 0; i < shootAnimSize; i++) {
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

	std::string granadePath = getResourcePath("enemy/granade");
	for (int i = 0; i < granadeAnimSize; i++) {
		granadeThrowTextures.push_back(game().getRenderer().loadTexture(granadePath + std::to_string(i + 1) + PNG));
	}

	bulletTexture = game().getRenderer().loadTexture(getResourcePath("bullet") + "bullet.png");

	granadeTexture = game().getRenderer().loadTexture(getResourcePath("bullet") + "granade.png");

	idleTexture = game().getRenderer().loadTexture(getResourcePath() + "enemy/idle.png");
	jumpTexture = idleTexture;

	spdlog::info("enemy loaded");
}

Enemy::~Enemy() {
	game().getCollisionManager().deregisterObject(this);
	for (auto &bullet : firedBullets) {
		game().getCollisionManager().deregisterObject(&bullet);
	}
	SDL_DestroyTexture(idleTexture);
	SDL_DestroyTexture(bulletTexture);
	SDL_DestroyTexture(granadeTexture);
	for (auto tex : granadeThrowTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : walkTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : shootTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : hurtTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : dieTextures)
		SDL_DestroyTexture(tex);
}

void Enemy::renderHurt() {
	if (currentHurtIdx >= 0) {
		currentTexture = hurtTextures[currentHurtIdx++];
		if (currentHurtIdx >= hurtAnimSize) {
			currentHurtIdx = -1;
			flip = SDL_FLIP_HORIZONTAL;
			sleep = 50;
		}
	}
}

void Enemy::renderGranadeThrow() {
	if (currentGranadeIdx >= 0) {
		currentTexture = granadeThrowTextures[currentGranadeIdx++];
		if (currentGranadeIdx >= granadeAnimSize) {
			currentGranadeIdx = -1;
		}
	}
}

void Enemy::renderGranade() {
	if (currentGranadeIdx != granadeAnimSize - 1)
		return;

	currentGranadeIdx++;

	// create bullet
	int x = boundingBox.x - 15; // offset to not walk into own bullet
	if (flip == SDL_FLIP_NONE)
		x += boundingBox.w + 10;

	int y = boundingBox.y - 10;

	firedBullets.emplace_back(x, y, flip, granadeTexture, true);
}

void Enemy::render() {

	if (!isAlive) {
		isVisible = false;
		return;
	}

	currentTexture = idleTexture;
	game().getCollisionManager().registerObject(this);
	intersection = game().getCollisionManager().checkCollision(this, boundingBox);

	--sleep;
	if (sleep == 0) {
		if (randomInt(0, 100) > 25)
			startShoot = true;
		else if (isBoss)
			currentGranadeIdx = 0;
		sleep = randomInt(30, 70);
	}

	renderShoot();
	renderGranadeThrow();
	renderGranade();
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
	if (isBoss)
		life = 200;
	ammo = 100;
	isVisible = true;
	startShoot = false;
}

bool Enemy::visible() {
	return isVisible;
}

int Enemy::demageValue() {
	return 5;
}
