#include "Game.hpp"
#include "managers/Renderer.hpp"
#include "utils/SDLException.hpp"
#include "utils/Utils.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <boost/program_options.hpp>
#include <spdlog/spdlog.h>

namespace po = boost::program_options;

void setLogLevel();

int main(int argc, char *argv[]) {

	setLogLevel();

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw SDLException("SDL_Init failed.");

	// init game
	Game game{};

	spdlog::info("start game");
	// game loop
	while (!game.isExit()) {
		game.renderClear();

		unsigned int renderStart = SDL_GetTicks();
		game.renderGame();

		unsigned int frameTime = SDL_GetTicks() - renderStart;
		if (frameTime < 30) {
			SDL_Delay(30 - frameTime);
		}

		game.renderUpdate();
	}

	// destroy SDL
	SDL_Quit();

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
