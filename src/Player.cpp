#include "headers/Player.hpp"
#include "headers/Constants.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <iostream>

Player::Player(std::array<int, 2> position, SDL_Renderer *renderer_, CollisionManager *collisionManager_) {
	renderer = renderer_;
	collisionManager = collisionManager_;

	id = "player";

	boundingBox.x = position[0];
	boundingBox.y = position[1];
	boundingBox.w = PLAYER_WIDTH;
	boundingBox.h = PLAYER_HEIGTH;

	collisionManager->registerObject(this);

	stepSize = 4;
	walkAnimSize = 14;
	shootAnimSize = 5;
	hurtAnimSize = 6;
	dieAnimSize = 7;

	keyDownEventMap.insert({SDLK_a, [this]() -> void { this->moveLeft(); }});
	keyDownEventMap.insert({SDLK_d, [this]() -> void { this->moveRight(); }});
	keyDownEventMap.insert({SDLK_w, [this]() -> void { this->jump(); }});
	keyDownEventMap.insert({SDLK_SPACE, [this]() -> void { this->shoot(); }});

	keyUpEventMap.insert({SDLK_a, [this]() -> void { this->stopMoveLeft(); }});
	keyUpEventMap.insert({SDLK_d, [this]() -> void { this->stopMoveRight(); }});

	drawBoundingBox = getArg<bool>("drawBoundingBox");
	spdlog::info(drawBoundingBox);

	loadTextures();

	spdlog::info("player initalized");
}

void Player::loadTextures() {

	// walk textures
	std::string walkPath = getResourcePath("player/walk");
	for (int i = 0; i < walkAnimSize; i++) {
		walkTextures.push_back(loadTexture(walkPath + std::to_string(i + 1) + PNG, renderer));
	}

	std::string shootPath = getResourcePath("player/shoot");
	for (int i = 0; i < shootAnimSize; i++) {
		shootTextures.push_back(loadTexture(shootPath + std::to_string(i + 1) + PNG, renderer));
	}

	std::string hurtPath = getResourcePath("player/hurt");
	for (int i = 0; i < hurtAnimSize; i++) {
		hurtTextures.push_back(loadTexture(hurtPath + std::to_string(i + 1) + PNG, renderer));
	}

	std::string diePath = getResourcePath("player/die");
	for (int i = 0; i < dieAnimSize; i++) {
		dieTextures.push_back(loadTexture(diePath + std::to_string(i + 1) + PNG, renderer));
	}

	jumpTexture = loadTexture(getResourcePath("player") + "jump.png", renderer);

	idleTexture = loadTexture(getResourcePath("player") + "idle.png", renderer);

	bulletTexture = loadTexture(getResourcePath("bullet") + "bullet.png", renderer);

	spdlog::info("player textures loaded");
}

void Player::jump() {
	if (!movement.up) {
		movement.up = true;
		startHeight = boundingBox.y;
		spdlog::debug("player jump");
	}
}

void Player::renderJump() {

	int step;
	if (movement.up) {
		step = -PLAYER_JUMP_SIZE;
	} else {
		return;
	}

	if (startHeight - PLAYER_JUMP_HEIGHT > boundingBox.y) {
		movement.up = false;
	}

	boundingBox.y += step;
	currentTexture = jumpTexture;
}

void Player::collisionAvoidance() {
	intersection = collisionManager->checkCollision(this, boundingBox);

	if (intersection.w > 0 && movement.right) {
		boundingBox.x -= intersection.w;
		// spdlog::debug(intersection.w);
	}
	if (intersection.w > 0 && movement.left) {
		boundingBox.x += intersection.w;
	}
	if (intersection.h > 0 && movement.up) {
		boundingBox.y += intersection.h;
		movement.up = false;
	}
}

void Player::render() {
	currentTexture = idleTexture;

	// render frame
	renderMove();
	renderJump();
	gravity(PLAYER_HEIGTH);
	renderShoot();
	renderHurt();
	renderDie();

	collisionAvoidance();

	renderTexture(currentTexture, renderer, boundingBox, flip);

	if (drawBoundingBox) {
		const SDL_Rect playerBB = boundingBox;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderDrawRect(renderer, &playerBB);
	}

	renderBullets();

	collisionManager->registerObject(this);
}

int Player::demageValue() {
	return 0;
}

int Player::getLife() {
	return life;
}

Player::~Player() {
	SDL_DestroyTexture(idleTexture);
	SDL_DestroyTexture(bulletTexture);
	SDL_DestroyTexture(jumpTexture);
	for (auto tex : walkTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : shootTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : hurtTextures)
		SDL_DestroyTexture(tex);
	for (auto tex : dieTextures)
		SDL_DestroyTexture(tex);

	// Mix_FreeChunk(gunSound);
	// Mix_FreeChunk(hurtSound);
}
