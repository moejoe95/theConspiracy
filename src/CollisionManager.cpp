#include "headers/CollisionManager.hpp"
#include "headers/Constants.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <string>

CollisionManager::CollisionManager(SDL_Renderer *renderer) : renderer(renderer) {}

void CollisionManager::registerObject(RenderObject *obj) {
	objectMap.insert({obj->getId(), obj});
}

void CollisionManager::deregisterObject(RenderObject *obj) {
	spdlog::debug("delete " + obj->getId());
	objectMap.erase(obj->getId());
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

				if (int dem = entry.second->demageValue()) {
					spdlog::debug("collision found " + entry.first + " -> " + currentObj->getId());
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
