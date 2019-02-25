#ifndef GRID_H
#define GRID_H

#include "AI/Node.h"
#include <list>
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/AIComponent.h"
#include "SDL_ttf.h"

class Grid 
{
public:
	Grid();
	Grid(Vector& screen, int width, int height);
	void render(SDL_Renderer* renderer);
	void update(Entity* ai);
	void processObstacles(CollisionSystem* system);
	void moddedDijkstra();
	void assignNeighbours();
	void getBestPath();

private:
	std::vector<std::vector<Node*>> m_grid;
	std::vector<Vector> m_visited;
	int m_width;
	int m_height;

	Node* m_goal = nullptr;
	Node* m_start = nullptr;
};
#endif // !GRID_H
