#ifndef GRID_H
#define GRID_H

#include <list>
#include <stack>
#include "SDL_ttf.h"
#include "AI/Tile.h"
#include "AI/NodePriorityQueue.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/AIComponent.h"

enum Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

class Grid 
{
public:
	Grid();
	Grid(Vector& screen, int width, int height);
	void render(SDL_Renderer* renderer);
	void update(Entity* ai);
	void processObstacles(CollisionSystem* system);
	std::vector<Vector> processPath(Vector& start, Vector& goal, int charWidth, int charHeight, int jumpHeight);

private:
	std::vector<std::vector<std::shared_ptr<Tile>>> m_grid; // 2d vector of grid tiles

	NodePriorityQueue<Vector, std::shared_ptr<Node>> m_open;

	std::vector<std::vector<std::shared_ptr<Node>>> m_nodes; // nodes for the location on the grid
	std::vector<Vector> m_close;
	std::vector<int> m_touchedNodes;

	Direction m_direction;
	std::map<Direction, Vector> m_nextCell;

	Vector m_location; // location in the grid
	Vector m_start;
	Vector m_goal;
	int m_width;
	int m_height;

	int m_openNode = 1;
	int m_closeNode = 2;
	int m_closeNodeCounter = 0;
	int m_stepHeuristic = 2;
};
#endif // !GRID_H
