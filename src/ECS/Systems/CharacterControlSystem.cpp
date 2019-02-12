#include "ECS/Systems/CharacterControlSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="e"></param>
void CharacterControlSystem::update(double dt, SDL_Event e)
{	
	for (Entity* entity : m_entities)
	{
        PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");
		
		ControllerState currentState = controller->getCurrentState();
		ControllerState previousState = controller->getPreviousState();

        //  Handle inputs.
        Vector acceleration;

        if (currentState.A && !physicsComponent->getJumping())
        {
			physicsComponent->setJumping(true);
            acceleration.y -= 1.5;
        }

        if (currentState.leftStick.x > controller->DEAD_ZONE && physicsComponent->getVelocity().x <= physicsComponent->getMaxVelocity().x)
        {
            acceleration.x += 0.075;
        }
        else if (currentState.leftStick.x < -controller->DEAD_ZONE && physicsComponent->getVelocity().x >= -physicsComponent->getMaxVelocity().x)
        {
            acceleration.x -= 0.075;
        }

        physicsComponent->setAcceleration(acceleration);
	}
}
