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
			column.push_back(std::make_shared<Tile>(i * width, j * width, m_width, m_height, count));
			count++;
		}
		count++;
		m_grid.push_back(column);
	}

	if (m_nodes.size() == 0 || m_nodes.size() != (m_width * m_height))
	{
		m_nodes = std::vector<std::vector<std::shared_ptr<Node>>>(m_width * m_height);
		m_close = std::vector<Vector>(m_width * m_height);
	}

	m_open = NodePriorityQueue<Vector, std::shared_ptr<Node>>(NodeComparer<Vector, std::shared_ptr<Node>>(m_nodes));
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
			//m_grid[i][j]->render(renderer);
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
							m_grid[i][j]->setTraversable(false);
						}
					}
				}
			}
		}
	}

	processPath(m_start, m_goal, 60,60, 6);

	time = SDL_GetTicks();
	std::cout << time << std::endl;
}

std::vector<Vector> Grid::processPath(Vector & start, Vector & goal, int charWidth, int charHeight, int jumpHeight)
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
		return std::vector<Vector>();
	}

	Node startNode = Node();
	startNode.setHeuristic(0);
	startNode.setEstimate(m_stepHeuristic);
	startNode.setParentIndex(start);
	startNode.setStatus(m_openNode);

	if (start.y < m_height - 1)
	{
		if(!m_grid[start.x][start.y + 1]->getTraversable())
		{
			start.z = 0;
			startNode.setJumpValue(start.z);
		}
		else
		{
			startNode.setJumpValue(jumpHeight * 2);
		}
	}

	m_nodes[m_grid[m_location.x][m_location.y]->getIndex()].push_back(std::make_shared<Node>(startNode));
	m_touchedNodes.push_back(m_grid[m_location.x][m_location.y]->getIndex());
	m_open.push(m_location);

	while (m_open.count() > 0 && !stop)
	{
		m_location = m_open.pop();
		if (m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->getStatus() == m_closeNode)
		{
			continue;
		}

		int locationX = m_location.x;
		int locationY = m_location.y;

		if (m_location.x == m_goal.x && m_location.y == m_goal.y)
		{
			m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->setStatus(m_closeNode);
			found = true;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			Vector newLocation = m_location + m_nextCell[(Direction)i];
			if (!m_grid[newLocation.x][newLocation.y]->getTraversable())
			{
				goto endLoop;
			}

			bool onGround = false;
			bool onCeiling = false;

			if (!m_grid[newLocation.x][newLocation.y + 1]->getTraversable())
			{
				onGround = true;
			}
			if (newLocation.y - 1 < 0)
			{
				onCeiling = true;
			}

			int jumpLength = m_nodes[m_grid[m_location.x][m_location.y]->getIndex()][m_location.z]->getJumpValue();
			short newJumpLength = jumpLength;
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
			else if (newLocation.y < m_location.y)
			{

			}
		}

	endLoop:
		continue;
	}

	return std::vector<Vector>();
}
