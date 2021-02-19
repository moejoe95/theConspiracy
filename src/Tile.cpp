#include "Tile.hpp"
#include "Game.hpp"
#include "utils/Utils.hpp"
#include <spdlog/spdlog.h>

int Tile::count = 0;

Tile::Tile(tson::TileObject tileObject, std::string layer) {

	id = std::to_string(count++);

	bool makesDemage = tileObject.getTile()->get<bool>("demage");
	if (makesDemage)
		demageIntValue = 1;

	healthValue = tileObject.getTile()->get<int>("health");
	ammoValue = tileObject.getTile()->get<int>("ammo");

	boundingBox.w = tileObject.getTile()->getImageSize().x;
	boundingBox.h = tileObject.getTile()->getImageSize().y;
	boundingBox.x = tileObject.getPosition().x;
	boundingBox.y = tileObject.getPosition().y - boundingBox.h + 32;

	std::string relPath = tileObject.getTile()->getImage().u8string();
	relPath.replace(0, 8, "");
	std::string absPath = getPath("", "data") + relPath;

	texture = game().getRenderer().loadTexture(absPath);

	isCollisionable = layer == "main" ? true : false;

	drawBoundingBox = getArg<bool>("drawBoundingBox");

	spdlog::debug("initialize tile " + id);
}

Tile::~Tile() {
	game().getCollisionManager().deregisterObject(this);
	SDL_DestroyTexture(texture);
}

void Tile::render() {
	game().getRenderer().drawTexture(texture, boundingBox);
	if (drawBoundingBox) {
		game().getRenderer().drawRect(boundingBox);
	}

	if (isCollisionable) {
		// TODO dont register in every timestep
		game().getCollisionManager().registerObject(this);
		game().getCollisionManager().checkCollision(this, boundingBox);
	}
}

const std::vector<SDL_Rect> Tile::getBoundingBoxes() {
	std::vector<SDL_Rect> boundingBoxes;
	boundingBoxes.push_back(boundingBox);
	return boundingBoxes;
}

void Tile::resetBoundingBox() {
	boundingBox.w = 0;
	boundingBox.h = 0;
}

int Tile::demageValue() {
	return demageIntValue;
}

void Tile::demage(int demage) {}

bool Tile::visible() {
	return isVisible;
}

void Tile::setInvisible() {
	isVisible = true;
}

int Tile::ammo() {
	return ammoValue;
}

int Tile::health() {
	return healthValue;
}

void Tile::resetHealth() {
	healthValue = 0;
}

void Tile::resetAmmo() {
	ammoValue = 0;
}
