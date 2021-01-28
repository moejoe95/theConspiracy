#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP

#include <SDL.h>
#include <string>
#include <vector>

enum class RenderType { Player, Enemy, Room, Bullet };

class RenderObject {

  public:
	std::string getId() { return id; }
	virtual const std::vector<SDL_Rect> getBoundingBoxes() = 0;
	virtual void demage(int demage) = 0;
	virtual int demageValue() = 0;
	virtual bool visible() = 0;

  protected:
	std::string id;
};

#endif // RENDER_OBJECT_HPP
