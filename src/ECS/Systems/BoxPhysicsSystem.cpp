#include "ECS/Systems/BoxPhysicsSystem.h"


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

		if (entity->getId == "PauseBox" && controller->m_paused = true)
		{	 
			if (positionComponent->getPos().y <= 200)
			{
				Vector v = { boxPhysics->getVelocity().x, boxPhysics->getVelocity().y + 1, 0 };

				boxPhysics->setVelocity(v);
			}
		}
	}
}