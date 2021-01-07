#ifndef BULLET_HPP
#define BULLET_HPP

#include "CollisionManager.hpp"
#include "RenderObject.hpp"
#include "Renderer.hpp"
#include <SDL.h>
#include <vector>

const int BULLET_WIDTH = 10;
const int BULLET_HEIGHT = 3;
const int BULLET_BLAST_ANIM_SIZE = 12;
const int BULLET_BLAST_SIZE = 40;
const int BULLET_VELOCITY = 10;

class Bullet : public RenderObject {

  public:
	Bullet(int x, int y, SDL_RendererFlip flip, Renderer *renderer, SDL_Texture *texture);

	void render();
	bool isOutOfSight();
	void demage(int demage) override;
	int demageValue() override;
	const std::vector<SDL_Rect> getBoundingBoxes() override;
	static int count;

  private:
	Renderer *renderer;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Texture *texture;
	SDL_Rect boundingBox;
	std::vector<SDL_Texture *> explodeTextures;

	bool outOfSight = false;
	int explodeIdx = -1;
};

#endif // BULLET_HPP
