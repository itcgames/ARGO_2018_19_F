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
			GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("GRAPHICS");
			CollisionComponent* collisionComponent = (CollisionComponent*)entity->getComponent("COLLISION");
			PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");

			ControllerState currentState = controller->getCurrentState();
			ControllerState previousState = controller->getPreviousState();

			//  Handle inputs.
			Vector acceleration;
			if (entity->getId() != "pauseBox")
			{
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

				if (currentState.B && !physicsComponent->getJumping())
				{
					graphicsComponent->setDestRect(43);
					SDL_Rect rect = { collisionComponent->getCollider().x, collisionComponent->getCollider().y, collisionComponent->getCollider().w, 43 };
					collisionComponent->setCollider(rect);
					Vector v = { positionComponent->getPos().x, positionComponent->getPos().y + 21 };
					positionComponent->setPos(v);
				}
				else
				{
					graphicsComponent->setDestRect(64);
					SDL_Rect rect = { collisionComponent->getCollider().x, collisionComponent->getCollider().y, collisionComponent->getCollider().w, 64 };
					collisionComponent->setCollider(rect);
				}

				physicsComponent->setAcceleration(acceleration);
			}
			
	}
}
