#ifndef GRID_H
#define GRID_H

#include "AI/Tile.h"
#include "AI/Node.h"
#include <list>
#include "ECS/Systems/CollisionSystem.h"
#include "SDL_ttf.h"

class Grid 
{
public:
	Grid();
	Grid(Vector& screen, int width, int height);
	void render(SDL_Renderer* renderer);
	void processObstacles(CollisionSystem* system);
	void moddedDijkstra();
	void assignNeighbours();
	void getBestPath();

private:
	std::vector<std::vector<Tile*>> m_grid;
	std::vector<Node*> m_nodes;
	int m_width;
	int m_height;
	Tile* m_goal = nullptr;
	Tile* m_start = nullptr;
};
#endif // !GRID_H
