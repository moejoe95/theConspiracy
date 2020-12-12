#ifndef ROOM_HPP
#define ROOM_HPP

#include "CollisionManager.hpp"
#include "RenderObject.hpp"
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
	~Room();
	Room(const std::string &roomFile, SDL_Renderer *renderer, CollisionManager *collisionManager);

	std::array<int, 2> playerStart;
	std::array<int, 2> enemyStart;

	void render();
	void demage(int demage) override;
	int demageValue() override;
	const std::vector<SDL_Rect> getBoundingBoxes() override;

  private:
	CollisionManager *collisionManager;
	std::string map;
	std::string background;
	std::map<std::string, std::string> tiles;
	std::vector<std::string> layout;
	bool drawBoundingBoxes;

	SDL_Renderer *renderer;
	SDL_Texture *ground_texture;
	SDL_Texture *platform_texture;
	SDL_Texture *background_texture;
	std::vector<SDL_Rect> boundingBoxes;

	void addBoundingBox(int x, int y);
	void loadTextures();
};

#endif // ROOM_HPP
