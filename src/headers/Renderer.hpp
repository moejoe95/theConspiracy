#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL.h>
#include <string>

class Renderer {

  public:
	Renderer();
	~Renderer();

	void clear();
	void update();
	SDL_Texture *loadTexture(const std::string &file);

	void drawText(const std::string &text, int x, int y);
	void drawRect(SDL_Rect rect);
	void drawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
	void drawTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void drawTexture(SDL_Texture *tex, SDL_Rect rect);
	void drawTexture(SDL_Texture *tex, SDL_Rect rect, SDL_RendererFlip flip);

  private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	int xOffset = 0;
};

#endif // RENDERER_HPP