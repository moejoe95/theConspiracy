#include "SDL_mixer.h"
#include "headers/Constants.hpp"
#include "headers/Game.hpp"
#include "headers/SDLException.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

namespace po = boost::program_options;

void setLogLevel();

int main(int argc, char *argv[]) {

	setLogLevel();

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw SDLException("SDL_Init failed.");

	SDL_Window *window = SDL_CreateWindow("the conspiracy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                                      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
		throw SDLException("SDL_CreateWindow failed.");

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		throw SDLException("SDL_CreateRenderer failed.");

	// init sound
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw SDLException("Mix_OpenAudio failed.");

	// init game
	Game game{"city.json", renderer};

	// game loop
	bool render = true;
	while (render) {
		SDL_RenderClear(renderer);

		unsigned int renderStart = SDL_GetTicks();
		render = game.renderGame();
		unsigned int frameTime = SDL_GetTicks() - renderStart;
		if (frameTime < 30) {
			SDL_Delay(30 - frameTime);
		}

		SDL_RenderPresent(renderer);
	}

	// destroy SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	Mix_CloseAudio();

	spdlog::info("quit game");

	return 0;
}

void setLogLevel() {
	std::string level = getArg<std::string>("SPDLOG_LEVEL");
	if (level == "debug") {
		spdlog::set_level(spdlog::level::debug);
	} else if (level == "error") {
		spdlog::set_level(spdlog::level::err);
	} else {
		spdlog::set_level(spdlog::level::info);
	}
	spdlog::info("set log level to: " + level);
}
