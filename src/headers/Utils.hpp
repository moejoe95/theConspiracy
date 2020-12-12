#ifndef UTIL_HPP
#define UTIL_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <array>
#include <boost/program_options.hpp>
#include <fstream>
#include <string>

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect boundingBox, SDL_RendererFlip flip);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect boundingBox);

void renderText(const std::string &text, SDL_Renderer *ren, int x, int y);

std::string getPath(const std::string &subDir, const std::string &dir);

std::string getResourcePath(const std::string &subDir = "");

std::string getMapsPath(const std::string &subDir = "");

std::string getBasePath(const std::string &subDir);

int getRandom(int start, int end);

template <typename T>
T getArg(const std::string &name) {
	namespace po = boost::program_options;

	std::string level;
	po::options_description config("Configuration");
	config.add_options()("drawBoundingBox", po::value<bool>()->default_value(false))(
	    "showStatus", po::value<bool>()->default_value(false))("SPDLOG_LEVEL",
	                                                           po::value<std::string>(&level)->default_value("info"));

	po::variables_map values;
	std::string settings = getBasePath("") + "settings.ini";
	std::ifstream iniFile(settings);
	po::store(parse_config_file(iniFile, config), values);
	notify(values);

	return values[name].as<T>();
}

#endif
