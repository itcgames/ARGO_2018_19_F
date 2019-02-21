#include "AI/Tile.h"

Tile::Tile(int x, int y, int width, int height)
{
	if (m_font == nullptr)
	{
		m_font = TTF_OpenFont(".//resources//AGENCYR.TTF", 50);
	}

	m_path = false;
	m_traversable = true;
	m_rect = new SDL_Rect({ x, y, width, height });
	m_position = Vector(x,y,0);
	m_colour = { 125, 125, 0, 255 };
}

void Tile::render(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, _strdup(std::to_string(m_weight).c_str()), m_colour);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect dest = *m_rect;
	dest.w = dest.w / 2;
	dest.h = dest.h / 2;


	SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
	if (m_path)
	{
		SDL_RenderFillRect(renderer, m_rect);
	}
	else
	{
		SDL_RenderDrawRect(renderer, m_rect);
	}

	SDL_RenderCopy(renderer, message, NULL, &dest);
	SDL_DestroyTexture(message);
	SDL_FreeSurface(surface);

}

void Tile::setGoal()
{
	m_colour = { 0,125,255,0 };
}

void Tile::setStart()
{
	m_colour = { 0,125,255,0 };
}

void Tile::setPath()
{
	m_path = true;
}

void Tile::setTraversable(bool traversable)
{
	m_traversable = traversable;
	if (!traversable)
	{
		m_colour = { 255,0,0,255 };
	}
}

bool Tile::getTraversable()
{
	return m_traversable;
}

SDL_Rect* Tile::getRect()
{
	return m_rect;
}


void Tile::setWeight(int weight)
{
	m_weight = weight;
}

int Tile::getWeight()
{
	return m_weight;
}

void Tile::addNeighbour(Tile * tile)
{
	m_neighbours.push_back(tile);
}

std::vector<Tile*>& Tile::getNeighbours()
{
	return m_neighbours;
}
