#include "Utils.hpp"
#include "SDLException.hpp"
#include <SDL.h>
#include <array>
#include <iostream>
#include <random>
#include <spdlog/spdlog.h>
#include <string>

std::string getPath(const std::string &subDir, const std::string &dir) {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		} else {
			spdlog::error(SDL_GetError());
			return "";
		}
	}
	size_t pos = baseRes.rfind("build");
	std::string ret = baseRes.substr(0, pos) + dir + PATH_SEP;
	return subDir.empty() ? ret : ret + subDir + PATH_SEP;
}

std::string getResourcePath(const std::string &subDir) {
	return getPath(subDir, "res");
}

std::string getMapsPath(const std::string &subDir) {
	return getPath(subDir, "tiled");
}

std::string getBasePath(const std::string &subDir) {
	return getPath(subDir, "");
}

int randomInt(int lower, int upper) {
	// TODO use c++ approach with uniform_int_distribution
	return lower + (std::rand() % (upper - lower + 1));
}
