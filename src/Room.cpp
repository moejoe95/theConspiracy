#include "headers/Room.hpp"
#include "headers/Constants.hpp"
#include "headers/Game.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using nlohmann::json;

Room::Room(const std::string &roomFile, SDL_Renderer *renderer, CollisionManager *collisionManager_)
    : renderer(renderer) {
	collisionManager = collisionManager_;
	id = "room1";

	std::ifstream i(getMapsPath("") + roomFile);
	json j;
	i >> j;

	j.at("map").get_to(map);
	j.at("background").get_to(background);
	j.at("layout").get_to(layout);
	j.at("tiles").get_to(tiles);
	j.at("player").get_to(playerStart);
	j.at("enemy").get_to(enemyStart);

	drawBoundingBoxes = getArg<bool>("drawBoundingBox");
	spdlog::info(drawBoundingBoxes);

	loadTextures();

	spdlog::info("room " + roomFile + " initalized");
}

void Room::loadTextures() {
	const std::string resPath = getResourcePath();
	ground_texture = loadTexture(resPath + "ground.png", renderer);
	platform_texture = loadTexture(resPath + "platform.png", renderer);
	background_texture = loadTexture(resPath + background, renderer);

	spdlog::info("loaded room textures");
}

void Room::addBoundingBox(int x, int y) {
	SDL_Rect boundingBox;
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = CELL_SIZE;
	boundingBox.h = CELL_SIZE;
	boundingBoxes.push_back(boundingBox);
}

void Room::render() {
	boundingBoxes.clear();
	renderTexture(background_texture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	int y = 0;
	for (std::string row : layout) {
		int x = 0;
		for (char cell : row) {
			if (cell == GROUND) {
				renderTexture(ground_texture, renderer, x, y);
				addBoundingBox(x, y);
			} else if (cell == PLAT) {
				renderTexture(platform_texture, renderer, x, y);
				addBoundingBox(x, y);
			}
			x += CELL_SIZE;
		}
		y += CELL_SIZE;
	}

	if (drawBoundingBoxes) {
		for (auto bb : boundingBoxes) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderDrawRect(renderer, &bb);
		}
	}

	collisionManager->registerObject(this);
	for (auto bb : boundingBoxes)
		collisionManager->checkCollision(this, bb);
}

const std::vector<SDL_Rect> Room::getBoundingBoxes() {
	return boundingBoxes;
}

int Room::demageValue() {
	return 0;
}

void Room::demage(int demage) {}

Room::~Room() {
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(ground_texture);
	SDL_DestroyTexture(platform_texture);
}
