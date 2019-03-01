#include "ECS/Systems/AISystem.h"

/// <summary>
/// 
/// </summary>
AISystem::AISystem() :
	m_state(new IdleState())
{
	Vector screen = Vector(1600, 900);
	m_grid = Grid(screen, 40, 48);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void AISystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");
		PhysicsComponent* physics = (PhysicsComponent*)entity->getComponent("PHYSICS");
		GraphicsComponent* graphics = (GraphicsComponent*)entity->getComponent("GRAPHICS");

		ControllerState controllerState;

		Vector feetPos = { position->getPos().x + graphics->getDestRect().w, position->getPos().y + graphics->getDestRect().h };

		std::string stateId = m_state->getStateId();
		std::shared_ptr<Node> currentNode = m_grid.getNextNode(m_grid.screenToGrid(feetPos));
		std::shared_ptr<Node> nextNode = currentNode->getNext();

		if (stateId == "Idle" || stateId == "Moving")
		{
			if (currentNode->getShouldJump())
			{
				controllerState.A = true;
			}

			if (nextNode->getLocation().x > position->getPos().x)
			{
				controllerState.leftStick.x = -1;
			}
			else if (nextNode->getLocation().x < position->getPos().x)
			{
				controllerState.leftStick.x = 1;
			}
		}
		else if (stateId == "Jump")
		{
			if (nextNode->getLocation().x > position->getPos().x)
			{
				controllerState.leftStick.x = -1;
			}
			else if (nextNode->getLocation().x < position->getPos().x)
			{
				controllerState.leftStick.x = 1;
			}
		}

		PlayerState* state = m_state->handleState(entity, controllerState);
		m_state->update(dt, entity);
		if (state != nullptr)
		{
			delete(m_state);
			m_state = state;
			m_state->enter(entity);
		}

		m_grid.update(entity);
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
	m_grid.render(renderer);
}
