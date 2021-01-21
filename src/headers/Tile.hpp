#ifndef TILE_HPP
#define TILE_HPP

#include "CollisionManager.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include "tileson_min.hpp"
#include <SDL.h>
#include <string>
#include <vector>

class Tile : public RenderObject {

  public:
	Tile(tson::TileObject tileObject, Renderer *renderer, CollisionManager *collisionManager, std::string layer);
	~Tile();

	SDL_Texture *texture;
	SDL_Rect boundingBox;

	void render();

	void demage(int demage) override;
	int demageValue() override;
	const std::vector<SDL_Rect> getBoundingBoxes() override;

  private:
	Renderer *renderer;
	CollisionManager *collisionManager;
	int demageIntValue = 0;
	bool drawBoundingBox;
	bool isCollisionable;
	static int count;
};

#endif // TILE_HPP
