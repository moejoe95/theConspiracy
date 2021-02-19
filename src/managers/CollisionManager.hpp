#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include "../RenderObject.hpp"
#include "Renderer.hpp"
#include <SDL.h>
#include <map>
#include <string>

class Bullet;

class CollisionManager {

  public:
	CollisionManager();
	~CollisionManager();

	void registerObject(RenderObject *obj);
	void deregisterObject(RenderObject *obj);
	void cleanBullets(std::vector<std::string> ids);
	SDL_Rect checkCollision(RenderObject *obj, SDL_Rect currentBB);

  private:
	void resetSDLRect(SDL_Rect &rect);
	void pickUpLife(RenderObject *player, RenderObject *tile);
	void pickUpAmmo(RenderObject *player, RenderObject *tile);

	std::map<std::string, RenderObject *> objectMap;
};

#endif // COLLISION_MANAGER_HPP