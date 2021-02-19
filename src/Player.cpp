#include "Player.hpp"
#include "../include/cereal/archives/json.hpp"
#include "Game.hpp"
#include "utils/Constants.hpp"
#include "utils/Utils.hpp"
#include <SDL.h>
#include <spdlog/spdlog.h>

Player::Player(std::array<int, 2> position) {
	id = "player";

	boundingBox.w = PLAYER_WIDTH;
	boundingBox.h = PLAYER_HEIGTH;
	boundingBox.x = position[0];
	boundingBox.y = position[1];

	game().getCollisionManager().registerObject(this);

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
	godMode = getArg<bool>("godMode");

	loadTextures();
}

void Player::loadTextures() {

	// walk textures
	std::string walkPath = getResourcePath("player/walk");
	for (int i = 0; i < walkAnimSize; i++) {
		walkTextures.push_back(game().getRenderer().loadTexture(walkPath + std::to_string(i + 1) + PNG));
	}

	std::string shootPath = getResourcePath("player/shoot");
	for (int i = 0; i < shootAnimSize; i++) {
		shootTextures.push_back(game().getRenderer().loadTexture(shootPath + std::to_string(i + 1) + PNG));
	}

	std::string hurtPath = getResourcePath("player/hurt");
	for (int i = 0; i < hurtAnimSize; i++) {
		hurtTextures.push_back(game().getRenderer().loadTexture(hurtPath + std::to_string(i + 1) + PNG));
	}

	std::string diePath = getResourcePath("player/die");
	for (int i = 0; i < dieAnimSize; i++) {
		dieTextures.push_back(game().getRenderer().loadTexture(diePath + std::to_string(i + 1) + PNG));
	}

	jumpTexture = game().getRenderer().loadTexture(getResourcePath("player") + "jump.png");

	idleTexture = game().getRenderer().loadTexture(getResourcePath("player") + "idle.png");

	bulletTexture = game().getRenderer().loadTexture(getResourcePath("bullet") + "bullet.png");

	spdlog::info("player initalized");
}

void Player::save() {
	spdlog::info("save player state");
	std::ofstream os("data/player.json");
	cereal::JSONOutputArchive oarchive(os);
	oarchive(*this);
}

void Player::load() {
	spdlog::info("load player state");
	if (std::filesystem::exists("data/player.json")) {
		std::ifstream is("data/player.json");
		cereal::JSONInputArchive iarchive(is);
		iarchive(*this);
	}
}

void Player::remove() {
	if (std::filesystem::exists("data/player.json")) {
		std::filesystem::remove("data/player.json");
	}
}

void Player::jump() {
	if (!movement.up && !movement.down) {
		movement.up = true;
		startHeight = boundingBox.y;
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
		if (!godMode)
			movement.down = true;
	}

	boundingBox.y += step;

	// collision avoidance
	SDL_Rect new_intersection = game().getCollisionManager().checkCollision(this, boundingBox);
	if (new_intersection.h > intersection.h) {
		boundingBox.y -= step;
		movement.up = false;
		movement.down = true;
	}

	currentTexture = jumpTexture;
}

void Player::render() {
	currentTexture = idleTexture;

	intersection = game().getCollisionManager().checkCollision(this, boundingBox);

	// render frame
	renderMove();
	renderJump();
	gravity();
	renderShoot();
	renderHurt();
	renderDie();

	renderBullets();

	game().getCollisionManager().registerObject(this);

	SDL_Rect offset; // offset for rendering
	offset.x = -30;
	offset.y = -20;
	offset.w = 60;
	offset.h = 20;
	game().getRenderer().drawTexture(currentTexture, boundingBox, offset, flip);

	if (drawBoundingBox) {
		const SDL_Rect playerBB = boundingBox;
		game().getRenderer().drawRect(playerBB);
	}

	// reset ammo if god
	if (godMode)
		ammo = 20;
}

int Player::demageValue() {
	return 0;
}

int Player::getLife() {
	return life;
}

int Player::getAmmo() {
	return ammo;
}

void Player::demage(int demage) {
	if (!godMode)
		Entity::demage(demage);
}

void Player::addAmmo(int newAmmo) {
	ammo += newAmmo;
}

void Player::addLife(int newLife) {
	life += newLife;
}

SDL_Rect Player::getPosition() {
	return boundingBox;
}

void Player::resetPosition(std::array<int, 2> position) {
	boundingBox.x = position[0];
	boundingBox.y = position[1];
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
}
