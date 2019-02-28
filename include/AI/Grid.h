#ifndef GRID_H
#define GRID_H

#include <list>
#include <stack>
#include "SDL_ttf.h"
#include "AI/Tile.h"
#include "AI/Node.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Components/AIComponent.h"

enum Direction
{
	EAST,
	WEST,
	NORTH,
	SOUTH
};

class Grid 
{
public:
	Grid();
	Grid(Vector& screen, int width, int height);
	void render(SDL_Renderer* renderer);
	void update(Entity* ai);
	void processObstacles(CollisionSystem* system);
	std::shared_ptr<Node> getNextNode(Vector location);

private:
	std::vector<std::vector<std::shared_ptr<Tile>>> m_grid; // 2d vector of grid tiles
	std::vector<std::shared_ptr<Node>> m_nodes;
	std::shared_ptr<Node> m_currentTarget;

	Direction m_direction;
	Vector m_location; // location in the grid
	Vector m_start;
	Vector m_goal;

	double m_clock;

	int m_gridWidth;
	int m_gridHeight;
	int m_tileWidth;
	int m_tileHeight;
};
#endif // !GRID_H
