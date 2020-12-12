#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include "RenderObject.hpp"
#include <SDL.h>
#include <map>
#include <string>

class CollisionManager {

  public:
	explicit CollisionManager(SDL_Renderer *renderer);
	~CollisionManager();

	void registerObject(RenderObject *obj);
	void deregisterObject(RenderObject *obj);
	SDL_Rect checkCollision(RenderObject *obj, SDL_Rect currentBB);

  private:
	void resetSDLRect(SDL_Rect &rect);

	SDL_Renderer *renderer;
	std::map<std::string, RenderObject *> objectMap;
};

#endif // ENEMY_HPP