#include "ECS/Systems/AISystem.h"

/// <summary>
/// 
/// </summary>
AISystem::AISystem() :
	m_state(new IdleState())
{
	Vector screen = Vector(1600, 900);
	m_grid = Grid(screen, 40, 48);	
	m_pairIndex = 0;
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void AISystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		AIComponent* aiComponent = (AIComponent*)entity->getComponent("AI");
		ControllerState controllerState;

		std::string stateId = m_state->getStateId();
		
		if (m_path.size() > 0)
		{
			std::pair<Vector, bool> nextNode = m_path[m_pairIndex];

			if (stateId != "Death" && stateId != "Victory")
			{
				if (stateId == "Idle" || stateId == "Moving")
				{
					if (nextNode.second)
					{
						controllerState.A = true;
					}

					if (nextNode.first.x > aiComponent->getGridLocation().x)
					{
						controllerState.leftStick.x = 1;
					}
					else if (nextNode.first.x < aiComponent->getGridLocation().x)
					{
						controllerState.leftStick.x = -1;
					}
				}
				else if (stateId == "Jump")
				{
					if (nextNode.first.x > aiComponent->getGridLocation().x)
					{
						controllerState.leftStick.x = 1;
					}
					else if (nextNode.first.x < aiComponent->getGridLocation().x)
					{
						controllerState.leftStick.x = -1;
					}
				}
			}

			if (nextNode.first.x >= aiComponent->getGridLocation().x && nextNode.first.x <= aiComponent->getGridLocation().x)
			{
				m_pairIndex++;
			}

			PlayerState* state = m_state->handleState(entity, controllerState);
			m_state->update(dt, entity);
			if (state != nullptr)
			{
				delete(m_state);
				m_state = state;
				m_state->enter(entity);
			}
		}
		else
		{
			m_grid.update(entity);
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="collisionSystem"></param>
void AISystem::processLevelEntities(CollisionSystem* collisionSystem)
{
	m_grid.processObstacles(collisionSystem);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void AISystem::render(SDL_Renderer * renderer)
{
	//m_grid.render(renderer);	//	Uncomment to render the ai grid.
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <returns></returns>
void AISystem::generatePath()
{
	std::vector<std::pair<Vector, bool>> path;
	
	do
	{
		std::shared_ptr<Node> currentNode;
		if (path.size() <= 0)
		{
			currentNode = m_grid.getNextNode(m_grid.getStart());
		}
		else
		{
			currentNode = m_grid.getNextNode(path[path.size() - 1].first);
		}
		
		if (currentNode->getNext() != std::shared_ptr<Node>())
		{
			Vector next = Vector(currentNode->getNext()->getLocation().x, currentNode->getNext()->getLocation().y);
			path.push_back(std::pair<Vector, bool>(next, currentNode->getNext()->getShouldJump()));
		}
	} while (path[path.size() - 1].first != m_grid.getGoal());

	m_path = path;
}
