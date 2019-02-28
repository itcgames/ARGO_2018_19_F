#ifndef TILE_H
#define TILE_H

#include "Vector/Vector.h"
#include <vector>
#include "SDL.h"
#include <string>
#include "SDL_ttf.h"

class Tile
{
public:
	Tile() {};
	Tile(int x , int y, int width, int height);
	void render(SDL_Renderer* renderer);

	void setGoal();
	void setStart();
	void setPath();
	void setTraversable(bool traversable);
	bool getTraversable();

	SDL_Rect* getRect();

	void setWeight(int weight);
	int getWeight();

	void addNeighbour(Tile* node);
	std::vector<Tile*>& getNeighbours();

private:
	TTF_Font * m_font;
	Vector parent;
	Vector m_position;
	SDL_Rect* m_rect;
	SDL_Color m_colour;
	std::vector<Tile*> m_neighbours;

	int m_jumpLength;
	int m_weight;
	bool m_traversable;
	bool m_path;
};
#endif // !TILE_H
