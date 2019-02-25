#ifndef GRID_H
#define GRID_H

#include "AI/Node.h"
#include "AI/NodePriorityQueue.h"
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

private:
	NodePriorityQueue<std::vector<std::shared_ptr<Node>>>* m_open;
	std::vector<std::vector<std::shared_ptr<Node>>> m_grid;
	std::vector<Vector> m_visited;
	int m_width;
	int m_height;

	std::shared_ptr<Node> m_goal = nullptr;
	std::shared_ptr<Node> m_start = nullptr;
};
#endif // !GRID_H
