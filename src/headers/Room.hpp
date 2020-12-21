#ifndef ROOM_HPP
#define ROOM_HPP

#include "CollisionManager.hpp"
#include "RenderObject.hpp"
#include "tileson_min.hpp"
#include <SDL.h>
#include <array>
#include <map>
#include <string>
#include <vector>

const char GROUND = 'g';
const char WALL = 'w';
const char CEIL = 'c';
const char PLAT = 'p';

class Room : public RenderObject {

  public:
	Room(const std::string &roomFile, SDL_Renderer *renderer, CollisionManager *collisionManager);

	std::array<int, 2> playerStart;
	std::array<int, 2> enemyStart;

	void render();
	void demage(int demage) override;
	int demageValue() override;
	const std::vector<SDL_Rect> getBoundingBoxes() override;

  private:
	CollisionManager *collisionManager;
	std::string drawMode;
	bool drawBoundingBox;

	SDL_Renderer *renderer;
	std::map<SDL_Texture *, SDL_Rect> textureMap;
	std::vector<SDL_Rect> boundingBoxes;

	SDL_Rect getSDLRect(tson::Vector2f position, tson::Vector2i imageSize, bool addBoundingBox);
	void loadTextures();
	void drawBoundingBoxes();
	void drawLayer(std::unique_ptr<tson::Map> &map, std::string name);
};

#endif // ROOM_HPP
