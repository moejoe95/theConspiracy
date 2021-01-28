#include "headers/CollisionManager.hpp"
#include "headers/Constants.hpp"
#include "headers/Player.hpp"
#include "headers/SoundManager.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <string>

CollisionManager::CollisionManager() {}

void CollisionManager::registerObject(RenderObject *obj) {
	objectMap.insert({obj->getId(), obj});
}

void CollisionManager::deregisterObject(RenderObject *obj) {
	spdlog::debug("delete " + obj->getId());
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

SDL_Rect CollisionManager::checkCollision(RenderObject *currentObj, const SDL_Rect currentBB) {
	SDL_Rect intersection;

	for (std::pair<std::string, RenderObject *> entry : objectMap) {
		if (entry.first == currentObj->getId())
			continue;
		for (auto bb : entry.second->getBoundingBoxes()) {
			if (SDL_IntersectRect(&currentBB, &bb, &intersection)) {

				if (!entry.second->visible())
					continue;

				auto p = dynamic_cast<Player *>(currentObj);
				auto t = dynamic_cast<Tile *>(entry.second);

				// refill life and remove box
				if (p && t && t->health() > 0) {
					p->addLife(t->health());
					t->resetHealth();
					t->boundingBox.w = 0;
					t->boundingBox.h = 0;
					SoundManager::getInstance().playCollectHealthSound();
				} else if (p && t && t->ammo() > 0) { // refill ammo and remove box
					p->addAmmo(t->ammo());
					t->resetAmmo();
					t->boundingBox.w = 0;
					t->boundingBox.h = 0;
					SoundManager::getInstance().playReloadGun();
				}

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
