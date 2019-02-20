#ifndef TILE_H
#define TILE_H

#include "Vector/Vector.h"
#include "SDL.h"

class Tile
{
public:
	Tile() {};
	Tile(int x , int y, int width, int height);
	void render(SDL_Renderer* renderer);

	void setTraversable(bool traversable);
	bool getTraversable();

	SDL_Rect* getRect();

private:
	Vector m_position;
	SDL_Rect* m_rect;
	bool m_traversable;
};
#endif // !TILE_H
