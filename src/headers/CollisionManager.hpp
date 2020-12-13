#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include "RenderObject.hpp"
#include <SDL.h>
#include <map>
#include <string>

class Bullet;

class CollisionManager {

  public:
	explicit CollisionManager(SDL_Renderer *renderer);
	~CollisionManager();

	// TODO: maybe better to use copy of RenderObjects?
	// if pointer, locactions must be updated when the are stored in
	// containers at the call site
	void registerObject(RenderObject *obj);
	void deregisterObject(RenderObject *obj);
	void cleanBullets(std::vector<std::string> ids);
	SDL_Rect checkCollision(RenderObject *obj, SDL_Rect currentBB);

  private:
	void resetSDLRect(SDL_Rect &rect);

	SDL_Renderer *renderer;
	std::map<std::string, RenderObject *> objectMap;
};

#endif // ENEMY_HPP