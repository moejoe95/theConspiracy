#include "headers/EventDispatcher.hpp"
#include "headers/Player.hpp"
#include <SDL.h>
#include <functional>
#include <map>

SDL_EventType dispatchKeyEvent(Player &player) {
	SDL_EventType type;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_KEYDOWN: {
			auto key = event.key.keysym.sym;
			if (player.keyDownEventMap.find(key) != player.keyDownEventMap.end()) {
				player.keyDownEventMap.find(key)->second();
			} else if (key == SDLK_ESCAPE) {
				type = SDL_QUIT;
			}
		} break;

		case SDL_KEYUP: {
			auto key = event.key.keysym.sym;
			if (player.keyUpEventMap.find(key) != player.keyUpEventMap.end()) {
				player.keyUpEventMap.find(key)->second();
			} else if (key == SDLK_ESCAPE) {
				type = SDL_QUIT;
			}
		} break;

		case SDL_QUIT:
			type = SDL_QUIT;
			break;
		}
	}

	return type;
}
