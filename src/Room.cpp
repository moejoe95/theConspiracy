#include "headers/Room.hpp"
#include "headers/Constants.hpp"
#include "headers/Game.hpp"
#include "headers/SoundManager.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <nlohmann/json.hpp>

using nlohmann::json;

Room::Room(const std::string &roomFile, Renderer *renderer, CollisionManager *collisionManager_) : renderer(renderer) {
	collisionManager = collisionManager_;
	id = "room1";

	drawBoundingBox = getArg<bool>("drawBoundingBox");
	drawMode = getArg<std::string>("drawMode");

	roomMaps.push_back(roomFile);
	// TODO second room
	roomMaps.push_back(roomFile);

	loadTextures(getMapsPath() + roomMaps[0]);

	// play backround
	SoundManager::getInstance().playBackgroundSound();

	spdlog::info("room " + roomFile + " initalized");
}

Room::~Room() {
	for (auto &textureMap : textureMapList) {
		for (auto &[tex, rect] : textureMap) {
			SDL_DestroyTexture(tex);
		}
	}
}

void Room::loadTextures(std::string mapPath) {

	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(fs::path(mapPath));

	playerStart[0] = map->get<int>("player.x");
	playerStart[1] = map->get<int>("player.y");
	goalX = map->get<int>("goal");

	textureMapList.clear();
	boundingBoxes.clear();

	if (map->getStatus() == tson::ParseStatus::OK) {

		drawLayer(map, "background");
		drawLayer(map, "decorations");
		drawLayer(map, "main");
	} else {
		spdlog::error("failed to parse map");
	}

	collisionManager->registerObject(this);
}

void Room::drawLayer(std::unique_ptr<tson::Map> &map, std::string name) {

	std::map<SDL_Texture *, SDL_Rect> textureMap;
	tson::Layer *layer = map->getLayer(name);
	for (auto &[pos, tileObject] : layer->getTileObjects()) {
		tson::Rect drawingRect = tileObject.getDrawingRect();

		bool addBB = false;
		if (name == "main")
			addBB = true;
		SDL_Rect rect = getSDLRect(tileObject.getPosition(), tileObject.getTile()->getImageSize(), addBB);

		std::string relPath = tileObject.getTile()->getImage().u8string();
		relPath.replace(0, 8, "");
		if (relPath.empty())
			continue;
		std::string absPath = getPath("", "data") + relPath;

		if (drawMode != "raw" || name == "main")
			textureMap.insert({renderer->loadTexture(absPath), rect});
	}
	textureMapList.push_back(textureMap);
}

void Room::drawBoundingBoxes() {
	if (drawBoundingBox) {
		for (auto bb : boundingBoxes) {
			renderer->drawRect(bb);
		}
	}
}

SDL_Rect Room::getSDLRect(tson::Vector2f position, tson::Vector2i imageSize, bool addBoundingBox) {
	SDL_Rect sdlRect;
	sdlRect.x = position.x;
	sdlRect.y = position.y - imageSize.y + 32;
	sdlRect.w = imageSize.x;
	sdlRect.h = imageSize.y;
	if (addBoundingBox)
		boundingBoxes.push_back(sdlRect);
	return sdlRect;
}

void Room::render() {

	for (auto &textureMap : textureMapList) {
		for (auto &[tex, rect] : textureMap) {
			renderer->drawTexture(tex, rect);
		}
	}

	drawBoundingBoxes();

	for (auto bb : boundingBoxes)
		collisionManager->checkCollision(this, bb);
}

bool Room::isOnGoal(int playerXPosition) {
	return playerXPosition > goalX;
}

void Room::nextRoom() {
	// TODO counter
	loadTextures(getMapsPath() + roomMaps[1]);
}

const std::vector<SDL_Rect> Room::getBoundingBoxes() {
	return boundingBoxes;
}

int Room::demageValue() {
	return 0;
}

void Room::demage(int demage) {}
