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



/// <summary>
/// 
/// </summary>
/// <param name="ai"></param>
void Grid::update(Entity * ai)
{
	CollisionComponent* collider = (CollisionComponent*)ai->getComponent("COLLISION");
	PositionComponent* position = (PositionComponent*)ai->getComponent("POSITION");
	AIComponent* aiComponent = (AIComponent*)ai->getComponent("AI");

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (m_grid[i][j]->getRect()->x <= position->getPos().x + collider->getCollider().w / 2  &&
				m_grid[i][j]->getRect()->x + m_grid[i][j]->getRect()->w / 2  >= position->getPos().x &&
				m_grid[i][j]->getRect()->y <= position->getPos().y + collider->getCollider().h / 2 &&
				m_grid[i][j]->getRect()->y + m_grid[i][j]->getRect()->h / 2  >= position->getPos().y)
			{
				if (j >= m_height - 1)
				{
					aiComponent->m_onGround = true;
					aiComponent->m_onPlatform = false;
				}
				else
				{
					if (!m_grid[i][j+1]->getTraversable())
					{
						aiComponent->m_onPlatform = true;
						aiComponent->m_onGround = false;
					}
				}
			}
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="system"></param>
void Grid::processObstacles(CollisionSystem * system)
{
	Uint32 time = SDL_GetTicks();
	std::cout << time << std::endl;

	for (Entity* entity : system->m_entities)
	{
		CollisionComponent* collider = (CollisionComponent*)entity->getComponent("COLLISION");
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");

		if (collider->getMainTag() != "player" && collider->getMainTag() != "cursor")
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
						if (collider->getMainTag() == "goal")
						{
							if (m_goal == NULL)
							{
								m_goal = m_grid[i][j + 1];
								m_grid[i][j + 1]->setGoal();
							}
						}
						else if (collider->getMainTag() == "start")
						{
							if (m_start == 0)
							{
								m_start = m_grid[i][j + 1];
								m_grid[i][j + 1]->setStart();
							}
						}
						else
						{
							if (j != 0)
							{
								if (m_grid[i][j - 1]->getTraversable() && collider->getMainTag() != "obstacle")
								{
									Vector pos = Vector(m_grid[i][j - 1]->getRect()->x + (m_grid[i][j - 1]->getRect()->w / 2), m_grid[i][j - 1]->getRect()->y + m_grid[i][j - 1]->getRect()->h / 2);
									m_nodes.push_back(new Node(pos));
									m_grid[i][j-1]->setWeight(-1);
								}
							}

							m_grid[i][j]->setTraversable(false);
						}
					}
				}
			}
		}
	}

	assignNeighbours();
	moddedDijkstra();
	getBestPath();

	time = SDL_GetTicks();
	std::cout << time << std::endl;
}



/// <summary>
/// 
/// </summary>
void Grid::assignNeighbours()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (i - 1 >= 0)
			{
				m_grid[i][j]->addNeighbour(m_grid[i - 1][j]); // top
			}
			if (i + 1 < m_width)
			{
				m_grid[i][j]->addNeighbour(m_grid[i + 1][j]); // bottom
			}
			if (j - 1 >= 0)
			{
				m_grid[i][j]->addNeighbour(m_grid[i][j - 1]); // left
			}
			if (j + 1 < m_height)
			{
				m_grid[i][j]->addNeighbour(m_grid[i][j + 1]); // right
			}
		}
	}
}

void Grid::getBestPath()
{
	std::list<Tile*> nodeList;
	nodeList.push_back(m_goal);

	while (nodeList.size() > 0 && nodeList.front() != m_start)
	{
		Tile* tile = nodeList.front();
		if (tile != m_goal)
		{
			tile->setPath();
		}
		nodeList.pop_front();

		int tileWeight = tile->getWeight();
		std::vector<Tile*> neighbours = tile->getNeighbours();
		for (int i = 0; i < neighbours.size(); i++)
		{
			Vector gridPos = Vector(neighbours[i]->getRect()->x / neighbours[i]->getRect()->w, neighbours[i]->getRect()->y / neighbours[i]->getRect()->h);
			if(neighbours[i]->getWeight() < tileWeight)
			{
				nodeList.push_front(neighbours[i]);
				break;
			}
		}
	}
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
				m_grid[i][j]->setWeight(0);
			}
		}
	}

	if (m_start != 0)
	{
		std::list<Tile*> tileList;
		m_start->setWeight(0);
		tileList.push_back(m_start);

		while (tileList.size() > 0)
		{
			Tile* currentID = tileList.front();
			tileList.pop_front();
			std::vector<Tile*> neighbours = currentID->getNeighbours();
			for (int i = 0; i < neighbours.size(); i++)
			{
				Tile* n = neighbours[i];
				int endNodeCost = currentID->getWeight() + 1;
				if (n->getWeight() <= 1)
				{
					if (std::find(tileList.begin(), tileList.end(), n) != tileList.end() == false)
					{
						tileList.push_back(n);
					}
					n->setWeight(endNodeCost);
				}
			}
		}
	}
}
