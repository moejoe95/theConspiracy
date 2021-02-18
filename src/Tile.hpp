#ifndef TILE_HPP
#define TILE_HPP

#include "../include/tileson/tileson_min.hpp"
#include "RenderObject.hpp"
#include "managers/CollisionManager.hpp"
#include "managers/Renderer.hpp"
#include <SDL.h>
#include <string>
#include <vector>

class Tile : public RenderObject {

  public:
	Tile(tson::TileObject tileObject, std::string layer);
	~Tile();

	SDL_Texture *texture;
	SDL_Rect boundingBox;

	void render();

	void demage(int demage) override;
	int demageValue() override;
	bool visible() override;
	const std::vector<SDL_Rect> getBoundingBoxes() override;
	int ammo();
	int health();
	void resetHealth();
	void resetAmmo();
	void setInvisible();

  private:
	int demageIntValue = 0;
	int ammoValue = 0;
	int healthValue = 0;
	bool isVisible = true;
	bool drawBoundingBox;
	bool isCollisionable;
	static int count;
};

#endif // TILE_HPP
