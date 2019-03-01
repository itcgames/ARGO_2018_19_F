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

	m_nodes = std::vector<std::shared_ptr<Node>>(m_gridWidth * m_gridHeight);
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
	m_currentTarget = getNextNode(aiComponent->getGridLocation());

	if (m_currentTarget->getNext() != std::shared_ptr<Node>())
	{
		aiComponent->setGridLocation(m_location.x, m_location.y);
		Vector next = Vector(m_currentTarget->getNext()->getLocation().x * m_tileWidth, (m_currentTarget->getNext()->getLocation().y * (m_tileHeight)-m_tileHeight));
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
		AIComponent* ai = (AIComponent*)entity->getComponent("AI");

		if (collider->getMainTag() != "cursor")
		{
			for (int i = 0; i < m_gridWidth; i++)
			{
				for (int j = 0; j < m_gridHeight; j++)
				{
					if (m_grid[i][j]->getRect()->x <= position->getPos().x + collider->getCollider().w / 1.15 &&
						m_grid[i][j]->getRect()->x + m_grid[i][j]->getRect()->w / 1.15 >= position->getPos().x &&
						m_grid[i][j]->getRect()->y <= position->getPos().y + collider->getCollider().h / 1.5 &&
						m_grid[i][j]->getRect()->y + m_grid[i][j]->getRect()->h / 1.5 >= position->getPos().y)
					{
						if (entity->getId() == "ai")
						{
							if (j < m_gridHeight - 1 && ai->getGridLocation().x == 0 && ai->getGridLocation().y == 0)
							{
								ai->setGridLocation(i, j + 2);
								m_start = Vector(i, j + 2);
								Node newNode = Node(m_start , m_nodes.size());
								newNode.setStart(true);
								m_nodes[m_grid[i][j + 2]->getIndex()] = std::make_shared<Node>(newNode);
								m_grid[i][j + 2]->fill(255, 255, 255, 255);
							}
						}
						if (collider->getMainTag() == "goal")
						{
							if (j < m_gridHeight - 1 && m_goal.x == 0 && m_goal.y == 0)
							{
								m_goal = Vector(i, j + 1);
								Node newNode = Node(Vector(i, j + 1, 0), m_nodes.size());
								newNode.setGoal(true);
								m_nodes[m_grid[i][j + 1]->getIndex()] = std::make_shared<Node>(newNode);
								m_grid[i][j + 1]->fill(255, 255, 255, 255);
							}
						}
						if (collider->getMainTag() == "platform")
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
			if (m_grid[i][j]->getTraversable())
			{
				if (i < m_gridWidth - 1 && i > 0) // if the current index is within range
				{
					if (j < m_gridHeight - 1 && j > 0)// if the current index is withing range
					{
						if (!m_grid[i][j + 1]->getTraversable()) // if the grid tile is a platform
						{
							Vector node = Vector(i, j , 0);
							float distanceToGoal = std::abs(Vector::Distance(node, m_goal));
							node.z = distanceToGoal;
							Node newNode = Node(node, m_nodes.size());
							if (m_grid[i + 1][j + 1]->getTraversable()) // one past and beside platform (edge)
							{
								newNode.setShouldJump(true);
							}

							m_grid[i][j]->fill(0, 255, 0, 255);
							m_nodes[m_grid[i][j]->getIndex()] = std::make_shared<Node>(newNode);
						}
					}
				}
			}
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="location"></param>
/// <returns></returns>
std::shared_ptr<Node> Grid::getNextNode(Vector location)
{
	m_location = location;
	float maxJump = 6;
	float maxHorizontal = 12;
	std::shared_ptr<Node> currentNode = m_nodes[m_grid[m_location.x][m_location.y]->getIndex()];

	// check the next immediate node
	if (currentNode != nullptr)
	{
		if (m_nodes[m_grid[m_location.x + 1][m_location.y]->getIndex()] != nullptr)
		{
			currentNode->setVisited(true);
			currentNode->setNext(m_nodes[m_grid[m_location.x + 1][m_location.y]->getIndex()]);
			m_grid[m_location.x][m_location.y]->fill(0, 255, 255, 255);
			m_location.x += 1;
			return currentNode;
		}
	}

	// iterate ahead of the character
	for (int i = m_location.x; i < m_gridWidth; i++)
	{
		if (m_location.y < maxJump)
		{
			maxJump = maxJump - m_location.y;
		}
		//iterate from the ground up to the max jump height
		for (int j = m_gridHeight - 1; j > m_location.y - maxJump && j >0; j--)
		{
			if (m_nodes[m_grid[i][j]->getIndex()] != std::shared_ptr<Node>()) // make sure the node you are checking isnt null
			{
				std::shared_ptr<Node> nextNode = m_nodes[m_grid[i][j]->getIndex()]; // node from map index
				if (nextNode != currentNode) // dont check the same node (if possible)
				{
					Vector currentLocation = currentNode->getLocation();
					Vector nextLocation = nextNode->getLocation();

					if (nextLocation.z < currentLocation.z) // weight (distance between) is less that current
					{
						if (j > currentLocation.y && currentLocation.y < 6) // if above the next node
						{
							maxHorizontal = 16;
						}
						if (std::abs(nextLocation.x - currentLocation.x) < maxHorizontal) // it can be reached
						{
							if (currentLocation.y < nextLocation.y) // below
							{
								currentNode->setNext(nextNode); // set the next node
								currentNode->setVisited(true); // set this node to be visited
								nextNode->setPrevious(currentNode); // set the next nodes previous node to be this node

								m_grid[currentLocation.x][currentLocation.y]->fill(0, 255, 255, 255);
								m_grid[nextLocation.x][nextLocation.y]->fill(0, 0, 255, 255);
								m_location.x = i;
								m_location.y = j;
								return currentNode;
							}
							else if(std::abs(currentLocation.y - nextLocation.y) < maxJump) // jump up
							{

								currentNode->setShouldJump(true);
								currentNode->setNext(nextNode); // set the next node
								currentNode->setVisited(true); // set this node to be visited
								nextNode->setPrevious(currentNode); // set the next nodes previous node to be this node

								m_grid[currentLocation.x][currentLocation.y]->fill(0, 255, 255, 255);
								m_grid[nextLocation.x][nextLocation.y]->fill(0, 0, 255, 255);
								m_location.x = i;
								m_location.y = j;
								return currentNode;
							}
						}
					}
					// cheat to the goal if needed
					else if (Vector::Distance(currentLocation, m_goal) <= 3)
					{
						currentNode->setNext(m_nodes[m_grid[m_goal.x][m_goal.y]->getIndex()]);
						return currentNode;
					}
				}
			}
		}
	}

	return currentNode; // return same node if no path detected
}



/// <summary>
/// Converts screen coordinates to grid coordinates.
/// </summary>
/// <param name="x">Integer representing the x component of the coordinates to be converted.</param>
/// <param name="y">Integer representing the y component of the coordinates to be converted.</param>
/// <returns>Vector of two integers that represent the grid coordinates.</returns>
Vector Grid::screenToGrid(int x, int y)
{
	return Vector(std::floor((x - x % m_tileWidth) / m_tileWidth), std::floor((y - y % m_tileHeight) / m_tileHeight));
}



/// <summary>
/// Converts screen coordinates to grid coordinates.
/// </summary>
/// <param name="position"></param>
/// <returns>Vector of two integers that represent the grid coordinates.</returns>
Vector Grid::screenToGrid(Vector& position)
{
	return Vector(std::floor((position.x - (int)position.x % m_tileWidth) / m_tileWidth), std::floor((position.y - (int)position.y % m_tileHeight) / m_tileHeight));
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int Grid::getTileWidth()
{
	return m_tileWidth;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int Grid::getTileHeight()
{
	return m_tileHeight;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Vector Grid::getStart()
{
	return m_start;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Vector Grid::getGoal()
{
	return m_goal;
}
