#include "Game.hpp"
#include "Renderer.hpp"
#include "utils/SDLException.hpp"
#include "SDL_mixer.h"
#include "utils/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

void setLogLevel();

int main(int argc, char *argv[]) {

	setLogLevel();

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw SDLException("SDL_Init failed.");

	// init sound
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw SDLException("Mix_OpenAudio failed.");

	// init game
	Game game{};

	// game loop
	bool render = true;
	while (render) {
		game.renderClear();

		unsigned int renderStart = SDL_GetTicks();
		render = game.renderGame();

		unsigned int frameTime = SDL_GetTicks() - renderStart;
		if (frameTime < 30) {
			SDL_Delay(30 - frameTime);
		}

		game.renderUpdate();
	}

	// destroy SDL

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
