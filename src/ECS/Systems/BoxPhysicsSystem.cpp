#include "ECS/Systems/BoxPhysicsSystem.h"


BoxPhysicsSystem::BoxPhysicsSystem() :
	m_paused(false)
{
}

/// <summary>
///  A loop for updating the physics of the 
///  pause / score / selection screen
/// </summary>
void BoxPhysicsSystem::update(double dt)
{

	for (Entity* entity : m_entities)
	{
		BoxPhysicsComponent* boxPhysics = (BoxPhysicsComponent*)entity->getComponent("BOXPHYSICS");
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");

		ControllerState currentState = controller->getCurrentState();
		ControllerState previousState = controller->getPreviousState();
		
		if (boxPhysics != nullptr && positionComponent != nullptr && controller != nullptr)
		{	
			
			if (!previousState.start && currentState.start)
			{
				m_paused = !m_paused;
				std::cout << m_paused << std::endl;
			}

			if (m_paused)
			{				
				if (positionComponent->getPos().y <= 25)
				{
					Vector v = { positionComponent->getPos().x, positionComponent->getPos().y + 20 };
					positionComponent->setPos(v);
				}
			}
			
			if (!m_paused)
			{
				if (positionComponent->getPos().y >= -1000)
				{
					Vector v = { positionComponent->getPos().x, positionComponent->getPos().y - 100 };
					positionComponent->setPos(v);
				}
			}
		}
	}
}



/// <summary>
/// returning the pause bool
/// </summary>
/// <returns></returns>
bool BoxPhysicsSystem::getPause()
{
	return m_paused;
}
