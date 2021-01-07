#include "headers/Renderer.hpp"
#include "headers/Constants.hpp"
#include "headers/SDLException.hpp"
#include "headers/Utils.hpp"
#include "spdlog/spdlog.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

Renderer::Renderer() {
	window = SDL_CreateWindow("the conspiracy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
	                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
		throw SDLException("SDL_CreateWindow failed.");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		throw SDLException("SDL_CreateRenderer failed.");
}

void Renderer::clear() {
	SDL_RenderClear(renderer);
}

void Renderer::update() {
	SDL_RenderPresent(renderer);
}

void Renderer::drawText(const std::string &text, int x, int y) {
	if (TTF_Init() < 0)
		throw SDLException("TTF_Init failed");

	std::string fontName = getResourcePath("") + "Hack-Regular.ttf";

	TTF_Font *font = TTF_OpenFont(fontName.c_str(), 20);
	if (!font)
		throw SDLException("Failed to load font " + fontName);

	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);
	SDL_Rect Message_rect;
	Message_rect.x = x;
	Message_rect.y = y;
	Message_rect.w = w;
	Message_rect.h = h;

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

void Renderer::drawRect(SDL_Rect rect) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::drawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
	// Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x + xOffset;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Renderer::drawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	drawTexture(tex, ren, x, y, w, h);
}

void Renderer::drawTexture(SDL_Texture *tex, SDL_Rect rect) {
	drawTexture(tex, rect, SDL_FLIP_NONE);
}

void Renderer::drawTexture(SDL_Texture *tex, SDL_Rect rect, SDL_RendererFlip flip) {
	rect.x += xOffset;
	SDL_RenderCopyEx(renderer, tex, NULL, &rect, 0, NULL, flip);
}

SDL_Texture *Renderer::loadTexture(const std::string &file) {
	SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
	if (!texture) {
		spdlog::error("loading textures " + file + " failed");
		throw SDLException("loadTexture failed.");
	}
	return texture;
}

void Renderer::setXOffset(int offset) {
	xOffset = offset;
}

Renderer::~Renderer() {
	IMG_Quit();
	spdlog::debug("destroy window");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
