#ifndef GRID_H
#define GRID_H

#include "AI/Tile.h"
#include "AI/Node.h"
#include "ECS/Systems/CollisionSystem.h"

class Grid
{
public:
	Grid();
	Grid(Vector& screen, int width, int height);
	void render(SDL_Renderer* renderer);
	void processObstacles(CollisionSystem* system);

private:
	std::vector<std::vector<Tile*>> m_grid;
	int m_width;
	int m_height;
};
#endif // !GRID_H
