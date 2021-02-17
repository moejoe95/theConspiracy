#ifndef ROOM_HPP
#define ROOM_HPP

#include "../include/tileson/tileson_min.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "Tile.hpp"
#include "managers/CollisionManager.hpp"
#include <SDL.h>
#include <array>
#include <map>
#include <string>
#include <vector>

class Room {

  public:
	Room();

	std::array<int, 2> playerStart;

	void render();
	bool isOnGoal(int playerX);
	bool checkSavePoint(int playerX);
	void resetSavePoint();
	bool nextRoom();
	void reset();
	std::vector<std::array<int, 2>> getEnemyPositions();
	bool hasBoss();
	std::array<int, 2> getBossPosition();

	// serializing
	template <class Archive>
	void serialize(Archive &archive) {
		archive(currentMapIdx);
	}

	void save();
	void load();
	void remove();

  private:
	int goalX;
	int savePointX;
	int savePointRenderTime = 50;
	int currentMapIdx = 0;

	std::vector<Tile> tiles;
	std::vector<std::string> maps;
	std::vector<std::array<int, 2>> enemyPositions;
	bool isBoss = false;
	std::array<int, 2> bossPosition;

	SDL_Rect getSDLRect(tson::Vector2f position, tson::Vector2i imageSize, bool addBoundingBox);
	void parseMap();

	void drawLayer(std::unique_ptr<tson::Map> &map, std::string name);
};

#endif // ROOM_HPP
