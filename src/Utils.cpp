#include "headers/Utils.hpp"
#include "headers/SDLException.hpp"
#include "spdlog/spdlog.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <array>
#include <iostream>
#include <random>
#include <string>

SDL_Texture *loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (!texture) {
		spdlog::error("loading textures " + file + " failed");
		throw SDLException("loadTexture failed.");
	}
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	// Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect boundingBox, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(ren, tex, NULL, &boundingBox, 0, NULL, flip);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect boundingBox) {
	renderTexture(tex, ren, boundingBox, SDL_FLIP_NONE);
}

void renderText(const std::string &text, SDL_Renderer *ren, int x, int y) {
	if (TTF_Init() < 0)
		throw SDLException("TTF_Init failed");

	std::string fontName = getResourcePath("") + "Hack-Regular.ttf";

	TTF_Font *font = TTF_OpenFont(fontName.c_str(), 20);
	if (!font)
		throw SDLException("Failed to load font " + fontName);

	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	SDL_Texture *Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);

	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);
	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = w;
	Message_rect.h = h;

	SDL_RenderCopy(ren, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

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
	return getPath(subDir, "maps");
}

std::string getBasePath(const std::string &subDir) {
	return getPath(subDir, "");
}

int getRandom(int start, int end) {
	std::random_device rd;                             // obtain a random number from hardware
	std::mt19937 gen(rd());                            // seed the generator
	std::uniform_int_distribution<> distr(start, end); // define the range

	return distr(gen);
}
