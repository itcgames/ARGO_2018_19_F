#include "AI/Tile.h"

Tile::Tile(int x, int y, int width, int height)
{
	m_traversable = true;
	m_rect = new SDL_Rect({ x, y, width, height });
	m_position = Vector(x,y);
}

void Tile::render(SDL_Renderer* renderer)
{
	if (m_weight == INT_MAX)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}

	SDL_RenderDrawRect(renderer, m_rect);
}

void Tile::setTraversable(bool traversable)
{
	m_traversable = traversable;
}

bool Tile::getTraversable()
{
	return m_traversable;
}

SDL_Rect* Tile::getRect()
{
	return m_rect;
}


void Tile::setWeight(float weight)
{
	m_weight = weight;
}

float Tile::getWeight()
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
