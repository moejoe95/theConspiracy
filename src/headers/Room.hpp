#ifndef ROOM_HPP
#define ROOM_HPP

#include "CollisionManager.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "tileson_min.hpp"
#include <SDL.h>
#include <array>
#include <map>
#include <string>
#include <vector>

class Room : public RenderObject {

  public:
	Room(const std::string &roomFile, Renderer *renderer, CollisionManager *collisionManager);
	~Room();

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

	Renderer *renderer;
	std::vector<std::map<SDL_Texture *, SDL_Rect>> textureMapList;
	std::vector<SDL_Rect> boundingBoxes;

	SDL_Rect getSDLRect(tson::Vector2f position, tson::Vector2i imageSize, bool addBoundingBox);
	void loadTextures();
	void drawBoundingBoxes();
	void drawLayer(std::unique_ptr<tson::Map> &map, std::string name);
};

#endif // ROOM_HPP
