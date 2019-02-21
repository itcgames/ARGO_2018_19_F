#ifndef TILE_H
#define TILE_H

#include "Vector/Vector.h"
#include <vector>
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

	void setWeight(float weight);
	float getWeight();

	void addNeighbour(Tile* node);
	std::vector<Tile*>& getNeighbours();

private:
	std::vector<Tile*> m_neighbours;
	Vector m_position;
	SDL_Rect* m_rect;
	bool m_traversable;
	float m_weight;
};
#endif // !TILE_H
