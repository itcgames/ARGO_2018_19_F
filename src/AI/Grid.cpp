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
	m_nextCell = {
		{ Direction::EAST, Vector::Vector(1,0)}, 
		{ Direction::WEST, Vector::Vector(-1,0)}, 
		{ Direction::NORTH, Vector::Vector(0,-1)}, 
		{ Direction::SOUTH, Vector::Vector(0,1)} };

	m_width = screen.x / width;
	m_height = screen.y / height;
	int count = 0;

	// setting up the grid - tile just has the tiles grid position and an impassable boolean
	for (int i = 0; i < m_width; i++)
	{
		std::vector<std::shared_ptr<Tile>> column;
		for (int j = 0; j < m_height; j++)
		{
			column.push_back(std::make_shared<Tile>(i * width, j * height, width, height, count));
			count++;
		}
		m_grid.push_back(column);
	}

	if (m_nodes.size() == 0 || m_nodes.size() != (m_width * m_height))
	{
		m_nodes = std::vector<std::vector<std::shared_ptr<Node>>>(m_width * m_height);
		m_close = std::vector<Vector>(m_width * m_height);
	}

	m_open = NodePriorityQueue<int, Vector, std::shared_ptr<Node>>(NodeComparer<int, Vector, std::shared_ptr<Node>>(m_nodes));
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

	std::vector<std::pair<int, Vector>> m_path = processPath(m_start, m_goal, 60, 60, 3);
	for (std::pair<int, Vector> pair : m_open.getQueue())
	{
		m_grid[pair.second.x][pair.second.y]->fill(255, 0, 0, 255);
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

		if (collider->m_tag != "player" && collider->m_tag != "cursor")
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
						if (entity->getId() == "start")
						{
							if (j < m_height - 1)
							{
								m_start = Vector(i, j + 1);
							}
						}
						if (entity->getId() == "goal")
						{
							if (j < m_height - 1)
							{
								m_goal = Vector(i, j + 1);
							}
						}
						if (entity->getId() == "obstacle" || entity->getId() == "platform")
						{
							m_grid[i][j]->fill(0,255,0,255);
							m_grid[i][j]->setTraversable(false);
						}
					}
				}
			}
		}
	}

	time = SDL_GetTicks();
	std::cout << time << std::endl;
}

std::vector<std::pair<int, Vector>> Grid::processPath(Vector & start, Vector & goal, int charWidth, int charHeight, int jumpHeight)
{
	// setup variables for path
	bool found = false;
	bool stop = false;
	bool stopped = false;
	m_closeNodeCounter = 0;
	m_openNode += 2;
	m_closeNode += 2;
	m_open.clear();

	m_location = start;
	m_goal = goal;

	// clear any visited neighbours paths in nodes
	while (m_touchedNodes.size() > 0)
	{
		int temp = m_touchedNodes.front();
		m_nodes[m_touchedNodes.front()].clear();
		m_touchedNodes.erase(m_touchedNodes.begin());
	}

	// if the goal is unreachable
	if (!m_grid[goal.x][goal.y]->getTraversable())
	{
		return std::vector<std::pair<int, Vector>>();
	}

	Node startNode = Node();
	startNode.setHeuristic(m_stepHeuristic);
	startNode.setEstimate(0);
	startNode.setParentIndex(start);
	startNode.setStatus(m_openNode);

	if (m_location.y < m_height - 1)
	{
		if(m_grid[m_location.x][m_location.y + 1]->getTraversable())
		{
			m_location.z = 0;
			startNode.setJumpValue(m_location.z);
		}
		else
		{
			startNode.setJumpValue(jumpHeight * 2);
		}
	}
	else
	{
		start.z = 0;
		startNode.setJumpValue(start.z);
	}

	m_nodes[m_grid[m_location.x][m_location.y]->getIndex()].push_back(std::make_shared<Node>(startNode));
	m_touchedNodes.push_back(m_grid[m_location.x][m_location.y]->getIndex());
	m_open.push(m_grid[m_location.x][m_location.y]->getIndex(), m_location, m_nodes);

	while (m_open.count() > 0 && !found)
	{
		std::pair<int, Vector> pair = m_open.pop();
		m_location = pair.second;
		if (m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->getStatus() == m_closeNode)
		{
			continue;
		}

		if (m_location.x == m_goal.x && m_location.y == m_goal.y)
		{
			m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->setStatus(m_closeNode);
			found = true;
			break;
		}

		// calculate neighbours - we only check non diagonal tiles so only 4 is needed
		for (int i = 0; i < 4; i++)
		{
			// returns a vector which is adjacent to the current location
			Vector newLocation = m_location + m_nextCell[(Direction)i];
			if (newLocation.x < 0 || newLocation.x >= m_width || newLocation.y < 0 || newLocation.y >= m_height)
			{
				continue; // if the neighbour can't be accesed ignore it
			}
			if (!m_grid[newLocation.x][newLocation.y]->getTraversable())
			{
				continue; // if the neighbour can't be accesed ignore it
			}

			m_grid[newLocation.x][newLocation.y]->fill(255, 255, 255, 255);

			// bools to check if the neighbour will cause the character to be at the roof or on a ground tile
			bool onGround = false;
			bool onCeiling = false;

			if (newLocation.y == m_height - 1 || !m_grid[newLocation.x][newLocation.y + 1]->getTraversable())
			{
				onGround = true; // if the tile below the neighbour cant be accesed
			}
			if (newLocation.y - 1 < 0)
			{
				onCeiling = true; // if the location is beyond the roof then that node is at the top
			}

			int jumpLength = m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->getJumpValue();
			int newJumpLength = jumpLength;

			if (onCeiling)
			{
				if (newLocation.x != m_location.x)
				{
					newJumpLength = std::max(jumpHeight * 2 + 1, jumpLength + 1);
				}
				else
				{
					newJumpLength = std::max(jumpHeight * 2, jumpLength + 2);
				}
			}
			else if (onGround)
			{
				newJumpLength = 0;
			}
			else if (newLocation.y < m_location.y) // neighbour above
			{
				if (jumpLength < 2 && jumpHeight > 2)
				{
					newJumpLength = 3;
				}
				else if (jumpLength % 2 == 0)
				{
					newJumpLength = jumpLength + 2;
				}
				else
				{
					newJumpLength = jumpLength + 1;
				}
			}
			else if (newLocation.y > m_location.y)
			{
				if (jumpLength % 2 == 0)
				{
					newJumpLength = std::max(jumpHeight * 2, jumpLength + 2);
				}
				else
				{
					newJumpLength = std::max(jumpHeight * 2, jumpLength + 1);
				}
			}
			else if (!onGround && newLocation.x != m_location.x)
			{
				newJumpLength = jumpLength + 1;
			}

			if (jumpLength >= 0 && jumpLength % 2 != 0 && newLocation.x != m_location.x)
			{
				continue;
			}

			if (newJumpLength > 3)
			{
				std::cout << "check" << std::endl;
			}

			if ((newJumpLength == 0 && newLocation.x != m_location.x && jumpLength + 1 >= jumpHeight * 2 + 6 && (jumpLength + 1 - (jumpHeight * 2 + 6)) % 8 <= 1)
				|| (newJumpLength >= jumpHeight * 2 + 6 && newLocation.x != m_location.x && (newJumpLength - (jumpHeight * 2 + 6)) % 8 != 7))
			{
				continue;
			}

			if (jumpLength >= jumpHeight * 2 && newLocation.y < m_location.y)
			{
				continue;
			}

			int value = (int)m_grid[m_location.x][m_location.y]->getTraversable();
			int newG = m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->getEstimate() + value + (newJumpLength / 4);

			if (m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()].size() > 0)
			{
				int lowestJump = INT_MAX;
				int lowestG = INT_MAX;
				bool moveHorizontal = false;

				for (int j = 0; j < m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()].size(); ++j)
				{
					if (m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()][j]->getJumpValue() < lowestJump)
					{
						lowestJump = m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()][j]->getJumpValue();
					}
					if (m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()][j]->getEstimate() < lowestG)
					{
						lowestG = m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()][j]->getEstimate();
					}
					if (m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()][j]->getJumpValue() % 2 == 0
						&& m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()][j]->getJumpValue() < jumpHeight * 2 + 6)
					{
						moveHorizontal = true;
					}
				}

				if (lowestG <= newG && lowestJump <= newJumpLength && (newJumpLength % 2 != 0 || newJumpLength >= jumpHeight * 2 + 6) || moveHorizontal)
				{
					continue;
				}
			}

			int heuristic = m_stepHeuristic * ((std::abs(newLocation.x - m_goal.x) + std::abs(newLocation.y - m_goal.y)));

			Node nextNode = Node();
			nextNode.setJumpValue(newJumpLength);
			nextNode.setParentIndex(m_location);
			nextNode.setEstimate(newG);
			nextNode.setHeuristic(newG + heuristic);
			nextNode.setStatus(m_openNode);

			if (m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()].size() == 0)
			{
				m_touchedNodes.push_back(m_grid[newLocation.x][newLocation.y]->getIndex());
			}

			m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()].push_back(std::make_shared<Node>(nextNode));
			m_open.push(m_grid[newLocation.x][newLocation.y]->getIndex(), Vector(newLocation.x, newLocation.y, m_nodes[m_grid[newLocation.x][newLocation.y]->getIndex()].size() - 1), m_nodes);
		}

		m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->setStatus(m_closeNode);
		m_closeNodeCounter++;
	}

	stopped = true;

	return m_open.getQueue();
}
