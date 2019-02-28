#ifndef TILE_H
#define TILE_H

#include "SDL_ttf.h"
#include "SDL.h"
#include "Vector/Vector.h"

class Tile
{
public:
	Tile()
	{
	}

	Tile(int x, int y, int width, int height, int index)
	{
		if (m_font == nullptr)
		{
			m_font = TTF_OpenFont(".//resources//AGENCYR.TTF", 50);
		}
		m_rect = new SDL_Rect({ x, y, width, height });
		m_colour = { 125, 125, 0, 255 };
		m_location = Vector(x, y);
		m_traversable = true;
		m_index = index;
	}


	SDL_Rect* getRect()
	{
		return m_rect;
	}

	bool getTraversable()
	{
		return m_traversable;
	}

	void setTraversable(bool traversable)
	{
		m_traversable = traversable;
	}

	int getIndex()
	{
		return m_index;
	}
	void setIndex(int index)
	{
		m_index = index;
	}

	void fill(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		m_colour = {r,g,b,a};
	}

	void render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
		SDL_RenderDrawRect(renderer, m_rect);
	}

private:
	bool m_traversable;
	Vector m_location;
	int m_index;

	// visualisation
	TTF_Font * m_font;
	SDL_Color m_colour;
	SDL_Rect* m_rect; // used for detection of world obstacles
};

#endif // !TILE_H
