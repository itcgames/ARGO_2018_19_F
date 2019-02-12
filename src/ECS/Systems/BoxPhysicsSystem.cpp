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
		
		if (boxPhysics != nullptr && positionComponent != nullptr && controller != nullptr)
		{
			if (controller->getPause())
			{
				if (positionComponent->getPos().y <= 200)
				{
					Vector v = { boxPhysics->getVelocity().x, boxPhysics->getVelocity().y + 1, 0 };

					boxPhysics->setVelocity(v);
					positionComponent->setPos(boxPhysics->getVelocity());
				}
			}
		}
	}
}