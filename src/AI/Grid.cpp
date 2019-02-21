#include "AI/Grid.h"

/// <summary>
/// 
/// </summary>
Grid::Grid()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="screen"></param>
/// <param name="width"></param>
/// <param name="height"></param>
Grid::Grid(Vector & screen, int width, int height)
{
	m_width = screen.x / width;
	m_height = screen.y / height;

	for (int i = 0; i < m_width; i++)
	{
		std::vector<Tile*> column;
		for (int j = 0; j < m_height; j++)
		{
			column.push_back(new Tile(i * width, j * height, width, height));
		}

		m_grid.push_back(column);
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Grid::render(SDL_Renderer * renderer)
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			m_grid[i][j]->render(renderer);
		}
	}

	for (Node* node : m_nodes)
	{
		node->render(renderer);
	}
}

void Grid::processObstacles(CollisionSystem * system)
{
	Uint32 time = SDL_GetTicks();
	std::cout << time << std::endl;

	for (Entity* entity : system->m_entities)
	{
		CollisionComponent* collider = (CollisionComponent*)entity->getComponent("COLLISION");
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");

		if (collider->m_tag == "obstacle" || collider->m_tag == "platform")
		{
			for (int i = 0; i < m_width; i++)
			{
				for (int j = 0; j < m_height; j++)
				{
					if (m_grid[i][j]->getRect()->x <= position->getPos().x + collider->getCollider().w / 1.25  &&
						m_grid[i][j]->getRect()->x + m_grid[i][j]->getRect()->w / 1.25 >= position->getPos().x &&
						m_grid[i][j]->getRect()->y <= position->getPos().y + collider->getCollider().h / 1.25 &&
						m_grid[i][j]->getRect()->y + m_grid[i][j]->getRect()->h / 1.25 >= position->getPos().y)
					{
						if (j != 0)
						{
							if (m_grid[i][j - 1]->getTraversable() && collider->m_tag != "obstacle")
							{
								Vector pos = Vector(m_grid[i][j - 1]->getRect()->x + (m_grid[i][j - 1]->getRect()->w / 2), m_grid[i][j - 1]->getRect()->y + m_grid[i][j - 1]->getRect()->h / 2);
								m_nodes.push_back(new Node(pos));
							}
						}
						m_grid[i][j]->setTraversable(false);
					}
				}
			}
		}
	}
	moddedDijkstra();

	time = SDL_GetTicks();
	std::cout << time << std::endl;
}



/// <summary>
/// 
/// </summary>
void Grid::moddedDijkstra()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (!m_grid[i][j]->getTraversable())
			{
				m_grid[i][j]->setWeight(INT_MAX);
			}
			else
			{
				m_grid[i][j]->setWeight(-1);
			}
		}
	}


}
