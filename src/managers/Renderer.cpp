#include "Renderer.hpp"
#include "../utils/Constants.hpp"
#include "../utils/SDLException.hpp"
#include "../utils/Utils.hpp"
#include <SDL_image.h>
#include <spdlog/spdlog.h>

Renderer::Renderer() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw SDLException("SDL_Init failed.");
	window = SDL_CreateWindow("the conspiracy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
	                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
		throw SDLException("SDL_CreateWindow failed.");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		throw SDLException("SDL_CreateRenderer failed.");

	if (TTF_Init() < 0)
		throw SDLException("TTF_Init failed");

	std::string fontName = getResourcePath("") + "Hack-Regular.ttf";

	TTF_Init();

	fontMenu = TTF_OpenFont(fontName.c_str(), 38);
	if (!fontMenu)
		throw SDLException("Failed to load font " + fontName);

	font = TTF_OpenFont(fontName.c_str(), 20);
	if (!font)
		throw SDLException("Failed to load font " + fontName);
}

Renderer::~Renderer() {
	TTF_CloseFont(font);
	TTF_CloseFont(fontMenu);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void Renderer::clear() {
	SDL_RenderClear(renderer);
}

void Renderer::update() {
	SDL_RenderPresent(renderer);
}

void Renderer::drawText(TTF_Font *font, const std::string &text, SDL_Rect rect) {
	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_RenderCopy(renderer, message, NULL, &rect);

	SDL_DestroyTexture(message);
	SDL_FreeSurface(surfaceMessage);
}

SDL_Rect Renderer::drawText(TTF_Font *font, const std::string &text, int x, int y) {

	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	drawText(font, text, rect);
	return rect;
}

SDL_Rect Renderer::drawText(const std::string &text, int x, int y) {
	return drawText(font, text, x, y);
}

SDL_Rect Renderer::drawText(TTF_Font *font, const std::string &text, int y) {

	int w, h;
	TTF_SizeText(font, text.c_str(), &w, &h);
	SDL_Rect rect;
	rect.x = SCREEN_WIDTH / 2 - w / 2;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	drawText(font, text, rect);
	return rect;
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

void Renderer::drawTexture(SDL_Texture *tex, SDL_Rect rect, SDL_Rect offset, SDL_RendererFlip flip) {
	rect.x += xOffset;
	rect.w += offset.w;
	rect.h += offset.h;
	rect.x += offset.x;
	rect.y += offset.y;
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

std::vector<SDL_Rect> Renderer::drawMenu() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	std::vector<SDL_Rect> buttons;

	buttons.push_back(drawText(fontMenu, "continue", 200));
	buttons.push_back(drawText(fontMenu, "new game", 275));
	buttons.push_back(drawText(fontMenu, "exit", 400));
	return buttons;
}

void Renderer::drawGameOverScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	drawText(fontMenu, "game over", 350);
}
