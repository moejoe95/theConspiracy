#ifndef ROOM_HPP
#define ROOM_HPP

#include "CollisionManager.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "Tile.hpp"
#include "tileson_min.hpp"
#include <SDL.h>
#include <array>
#include <map>
#include <string>
#include <vector>

class Room {

  public:
	Room(Renderer *renderer, CollisionManager *collisionManager);

	std::array<int, 2> playerStart;
	std::array<int, 2> enemyStart;

	void render();
	bool isOnGoal(int playerX);
	bool checkSavePoint(int playerX);
	void resetSavePoint();
	void nextRoom();

	// serializing
	template <class Archive>
	void serialize(Archive &archive) {
		archive(currentMapIdx);
	}

  private:
	CollisionManager *collisionManager;
	int goalX;
	int savePointX;
	int savePointRenderTime = 50;
	int currentMapIdx = 0;

	Renderer *renderer;
	std::vector<Tile> tiles;
	std::vector<std::string> maps;

	SDL_Rect getSDLRect(tson::Vector2f position, tson::Vector2i imageSize, bool addBoundingBox);
	void parseMap();

	void drawLayer(std::unique_ptr<tson::Map> &map, std::string name);
};

#endif // ROOM_HPP
