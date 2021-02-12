#include "headers/Room.hpp"
#include "headers/Constants.hpp"
#include "headers/Game.hpp"
#include "headers/SoundManager.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <nlohmann/json.hpp>

using nlohmann::json;

Room::Room(Renderer *renderer, CollisionManager *collisionManager_) : renderer(renderer) {
	collisionManager = collisionManager_;

	// queue up rooms
	maps.push_back("map1.json");
	maps.push_back("map2.json");
	maps.push_back("map3.json");

	// play backround
	SoundManager::getInstance().playBackgroundSound();

	spdlog::info("room initalized");

	// parse first map
	parseMap();
}

void Room::parseMap() {

	auto mapPath = getMapsPath() + maps[currentMapIdx];
	currentMapIdx++;

	tson::Tileson parser;
	std::unique_ptr<tson::Map> map = parser.parse(fs::path(mapPath));

	// read properties of map
	playerStart[0] = map->get<int>("player.x");
	playerStart[1] = map->get<int>("player.y");
	goalX = map->get<int>("goal");
	savePointX = map->get<int>("savepoint");

	for (auto &t : tiles) {
		collisionManager->deregisterObject(&t);
	}
	tiles.clear();

	if (map->getStatus() == tson::ParseStatus::OK) {
		drawLayer(map, "background");
		drawLayer(map, "decorations");
		drawLayer(map, "main");
	} else {
		spdlog::error("failed to parse map");
	}
}

void Room::drawLayer(std::unique_ptr<tson::Map> &map, std::string name) {
	tson::Layer *layer = map->getLayer(name);
	for (auto &[pos, tileObject] : layer->getTileObjects()) {
		if (tileObject.getTile()->get<bool>("enemy")) {
			int x = tileObject.getPosition().x;
			int y = tileObject.getPosition().y;
			std::array<int, 2> p = {x, y};
			enemyPositions.push_back(p);
		} else {
			tiles.emplace_back(tileObject, renderer, collisionManager, name);
		}
	}
}

std::vector<std::array<int, 2>> Room::getEnemyPositions() {
	return enemyPositions;
}

void Room::render() {
	for (auto &t : tiles) {
		t.render();
	}
}

bool Room::isOnGoal(int playerXPosition) {
	return playerXPosition > goalX;
}

bool Room::checkSavePoint(int playerXPosition) {
	if (savePointRenderTime > 0 && playerXPosition > savePointX) {
		renderer->drawText("game saved...", SCREEN_WIDTH - 160, 15);
		savePointRenderTime--;
		if (savePointRenderTime == 49) {
			spdlog::debug("player hit save point");
			return true;
		}
	}
	return false;
}

void Room::resetSavePoint() {
	savePointRenderTime = 50;
}

void Room::nextRoom() {
	// TODO counter
	parseMap();
}
