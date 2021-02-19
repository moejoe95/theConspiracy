#ifndef ROOM_HPP
#define ROOM_HPP

#include "../include/tileson/tileson_min.hpp"
#include "RenderObject.hpp"
#include "Tile.hpp"
#include "managers/CollisionManager.hpp"
#include "managers/Renderer.hpp"
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
	std::array<int, 2> getBossPosition();
	bool hasBoss();
	void parseMap();

	// serializing
	template <class Archive>
	void serialize(Archive &archive) {
		archive(currentMapIdx);
	}

	void save();
	void load();
	void remove();

  private:
	SDL_Rect getSDLRect(tson::Vector2f position, tson::Vector2i imageSize, bool addBoundingBox);

	void drawLayer(std::unique_ptr<tson::Map> &map, std::string name);

	std::vector<Tile> tiles;
	std::vector<std::string> maps;
	std::vector<std::array<int, 2>> enemyPositions;
	std::array<int, 2> bossPosition;

	bool isBoss = false;
	int goalX;
	int savePointX;
	int savePointRenderTime = 50;
	int currentMapIdx = 0;
};

#endif // ROOM_HPP
