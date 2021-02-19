#include "CollisionManager.hpp"
#include "../Game.hpp"
#include "../Player.hpp"
#include <spdlog/spdlog.h>
#include <string>

CollisionManager::CollisionManager() {}

void CollisionManager::registerObject(RenderObject *obj) {
	objectMap.insert({obj->getId(), obj});
}

void CollisionManager::deregisterObject(RenderObject *obj) {
	objectMap.erase(obj->getId());
}

void CollisionManager::cleanBullets(std::vector<std::string> ids) {
	for (auto bulletId : ids) {
		objectMap.erase(bulletId);
	}
}

void CollisionManager::resetSDLRect(SDL_Rect &rect) {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

void CollisionManager::pickUpLife(RenderObject *player, RenderObject *tile) {
	auto p = dynamic_cast<Player *>(player);
	auto t = dynamic_cast<Tile *>(tile);

	if (p && t && t->health() > 0) {
		p->addLife(t->health());
		t->resetHealth();
		t->resetBoundingBox();
		game().getSoundManager().playCollectHealthSound();
		spdlog::info("pick up life box");
	}
}

void CollisionManager::pickUpAmmo(RenderObject *player, RenderObject *tile) {
	auto p = dynamic_cast<Player *>(player);
	auto t = dynamic_cast<Tile *>(tile);

	if (p && t && t->ammo() > 0) {
		p->addAmmo(t->ammo());
		t->resetAmmo();
		t->resetBoundingBox();
		game().getSoundManager().playReloadGun();
		spdlog::info("pick up life ammo box");
	}
}

SDL_Rect CollisionManager::checkCollision(RenderObject *currentObj, const SDL_Rect currentBB) {
	SDL_Rect intersection;

	for (std::pair<std::string, RenderObject *> entry : objectMap) {
		if (entry.first == currentObj->getId())
			continue;
		for (auto bb : entry.second->getBoundingBoxes()) {
			if (SDL_IntersectRect(&currentBB, &bb, &intersection)) {

				if (!entry.second->visible() || !currentObj->visible())
					continue;

				pickUpLife(currentObj, entry.second);
				pickUpAmmo(currentObj, entry.second);

				if (int dem = entry.second->demageValue()) {
					entry.second->demage(0);
					currentObj->demage(dem);
				}
				return intersection;
			}
		}
	}
	resetSDLRect(intersection);
	return intersection;
}

CollisionManager::~CollisionManager() {}
