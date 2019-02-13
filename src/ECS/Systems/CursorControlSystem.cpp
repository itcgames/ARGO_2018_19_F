#include "ECS/Systems/CursorControlSystem.h"



CursorControlSystem::CursorControlSystem()
{
}


CursorControlSystem::~CursorControlSystem()
{
}

void CursorControlSystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");
		CollisionComponent* collisionComponent = (CollisionComponent*)entity->getComponent("COLLISION");
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");

		ControllerState currentState = controller->getCurrentState();
		ControllerState previousState = controller->getPreviousState();

		if (entity->getId() == "cursor" )
		{
			if (currentState.leftStick.x > controller->DEAD_ZONE )
			{
				Vector v = positionComponent->getPos();
				v.x = positionComponent->getPos().x + 1;

				positionComponent->setPos(v);// += 0.075;
			}
			else if (currentState.leftStick.x < -controller->DEAD_ZONE)
			{
				Vector v = positionComponent->getPos();
				v.x = positionComponent->getPos().x - 1;

				positionComponent->setPos(v);
			}

			if (currentState.leftStick.y > controller->DEAD_ZONE)
			{
				Vector v = positionComponent->getPos();
				v.y = positionComponent->getPos().y + 1;

				positionComponent->setPos(v);
			}
			else if (currentState.leftStick.y < -controller->DEAD_ZONE)
			{
				Vector v = positionComponent->getPos();
				v.y = positionComponent->getPos().y - 1;
				positionComponent->setPos(v);
			}
		}
	}
}