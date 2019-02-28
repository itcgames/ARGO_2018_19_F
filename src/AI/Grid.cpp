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
	m_gridWidth = screen.x / width;
	m_gridHeight = screen.y / height;
	m_tileWidth = width;
	m_tileHeight = height;
	int count = 0;
	m_clock = 0;

	// setting up the grid - tile just has the tiles grid position and an impassable boolean
	for (int i = 0; i < m_gridWidth; i++)
	{
		std::vector<std::shared_ptr<Tile>> column;
		for (int j = 0; j < m_gridHeight; j++)
		{
			column.push_back(std::make_shared<Tile>(i * width, j * height, m_tileWidth, m_tileHeight, count));
			count++;
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
	for (int i = 0; i < m_gridWidth; i++)
	{
		for (int j = 0; j < m_gridHeight; j++)
		{
			m_grid[i][j]->render(renderer);
		}
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

	// check the grid and if the player is colliding with the grid square update its location in the grid
	m_currentTarget = getNextNode(position->getPos());
	if (m_currentTarget->getNext() != std::shared_ptr<Node>())
	{
		Vector next = Vector(m_currentTarget->getNext()->getLocation().x * m_tileWidth, m_currentTarget->getNext()->getLocation().y * m_tileHeight - m_tileHeight);
		position->setPos(next);
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="system"></param>
void Grid::processObstacles(CollisionSystem * system)
{
	for (Entity* entity : system->m_entities)
	{
		CollisionComponent* collider = (CollisionComponent*)entity->getComponent("COLLISION");
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");

		if (collider->getMainTag() != "player" && collider->getMainTag() != "cursor")
		{
			for (int i = 0; i < m_gridWidth; i++)
			{
				for (int j = 0; j < m_gridHeight; j++)
				{
					if (m_grid[i][j]->getRect()->x <= position->getPos().x + collider->getCollider().w / 1.25  &&
						m_grid[i][j]->getRect()->x + m_grid[i][j]->getRect()->w / 1.25 >= position->getPos().x &&
						m_grid[i][j]->getRect()->y <= position->getPos().y + collider->getCollider().h / 1.25 &&
						m_grid[i][j]->getRect()->y + m_grid[i][j]->getRect()->h / 1.25 >= position->getPos().y)
					{
						if (entity->getId() == "start")

						{
							if (j < m_gridHeight - 1)
							{
								m_start = Vector(i, j + 1);
								Node newNode = Node(Vector(i, j + 1, 0), m_nodes.size());
								newNode.setStart(true);
								m_nodes.push_back(std::make_shared<Node>(newNode));
								m_currentTarget = std::make_shared<Node>(newNode);
								m_grid[i][j + 1]->fill(255, 255, 255, 255);
							}
						}
						if (entity->getId() == "goal")
						{
							if (j < m_gridHeight - 1)
							{
								m_goal = Vector(i, j + 1);
								Node newNode = Node(Vector(i, j + 1, 0), m_nodes.size());
								newNode.setGoal(true);
								m_nodes.push_back(std::make_shared<Node>(newNode));
								m_grid[i][j + 1]->fill(255, 255, 255, 255);
							}
						}
						if (entity->getId() == "obstacle" || entity->getId() == "platform")
						{
							m_grid[i][j]->fill(255, 0, 0, 255);

							m_grid[i][j]->setTraversable(false);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < m_gridWidth; i++)
	{
		for (int j = 0; j < m_gridHeight; j++)
		{
			if (!m_grid[i][j]->getTraversable())
			{
				if (i < m_gridWidth - 1 && i > 0) // if the current index is withing range
				{
					if (j < m_gridHeight - 1 && j > 0)
					{
						if (m_grid[i][j - 1]->getTraversable())
						{
							Node newNode = Node(Vector(i, j - 1, 0), m_nodes.size());
							if (m_grid[i + 1][j]->getTraversable())
							{
								newNode.setShouldJump(true);
							}

							m_grid[i][j - 1]->fill(0, 255, 0, 255);
							m_nodes.push_back(std::make_shared<Node>(newNode));
						}
					}
				}
			}
		}
	}
}

std::shared_ptr<Node> Grid::getNextNode(Vector location)
{
	m_location = Vector(std::abs((int)(location.x / m_tileWidth)), std::abs(int((location.y + m_tileHeight ))/ m_tileHeight));
	float maxJump = 6;
	float maxHorizontal = 8;
	std::shared_ptr<Node> m_newNode = m_currentTarget;
	m_currentTarget.reset();

	// look for the next forward node and 
	// check that it can be reached with a jump and move
	for (std::shared_ptr<Node> node : m_nodes) // iterate through nodes
	{
		Vector currentLocation = node->getLocation();
		if (m_location.x == currentLocation.x && m_location.y == currentLocation.y)
		{
			for (std::shared_ptr<Node> nextNode : m_nodes) // check against other nodes
			{
				Vector nextLocation = nextNode->getLocation();
				if (node != nextNode && !nextNode->getVisited())
				{
					if (!node->getGoBack()) // if going forward
					{
						if (nextLocation.x > currentLocation.x) // its ahead on the grid
						{
							if (std::abs(nextLocation.x - currentLocation.x) < maxHorizontal &&  std::abs(currentLocation.y - nextLocation.y) < maxJump) // it can be reached
							{
								if (currentLocation.y - nextLocation.y < maxJump || std::abs(nextLocation.x - currentLocation.x) > 2)
								{
									node->setShouldJump(true);
								}

								node->setNext(nextNode); // set the next node
								node->setVisited(true); // set this node to be visited
								nextNode->setPrevious(node); // set the next nodes previous node to be this node

								m_grid[currentLocation.x][currentLocation.y]->fill(0, 0, 0, 255);
								m_grid[nextLocation.x][nextLocation.y]->fill(0, 0, 255, 255);
								return node;
							}
							else // if it cant be reached trigger return to previous
							{
								continue;
							}
						}
						else if(nextLocation.y < currentLocation.y) // its above on the grid
						{
							if (std::abs(nextLocation.x - currentLocation.x) < maxHorizontal &&  std::abs(currentLocation.y - nextLocation.y) < maxJump) // it can be reached
							{
								if (currentLocation.y - nextLocation.y < maxJump)
								{
									node->setShouldJump(true);
								}

								node->setNext(nextNode); // set the next node
								node->setVisited(true); // set this node to be visited
								nextNode->setPrevious(node); // set the next nodes previous node to be this node
								m_grid[currentLocation.x][currentLocation.y]->fill(0, 0, 0, 255);
								m_grid[nextLocation.x][nextLocation.y]->fill(0, 0, 255, 255);
								return node;
							}
							else // if it cant be reached trigger return to previous
							{
								continue;
							}
						}
					}
					else // going back
					{
						return node->getPrevious();
					}
				}
			}
		}
	}

	return m_newNode;
}

