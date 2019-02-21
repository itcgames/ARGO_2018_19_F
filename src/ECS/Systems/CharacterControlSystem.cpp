#include "ECS/Systems/CharacterControlSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void CharacterControlSystem::update(double dt)
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

		if (physicsComponent != nullptr && controller != nullptr)
		{
			if (entity->getId() != "pauseBox" && entity->getId() != "cursor")
			{
				Vector velocity = physicsComponent->getVelocity();

				PlayerState* state = m_state->handleState(entity, currentState);
				m_state->update(dt, entity);
				if (state != nullptr)
				{
					delete(m_state);
					m_state = state;
					m_state->enter(entity);
				}

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

				if (currentState.leftStick.x < controller->DEAD_ZONE && currentState.leftStick.x > -controller->DEAD_ZONE)
				{
					if (!physicsComponent->getJumping())
					{
						acceleration.x = 0;
						velocity.x = 0;
					}
				}

				if (currentState.B && !physicsComponent->getJumping())
				{
					SDL_Rect destRect = graphicsComponent->getDestRect();
					graphicsComponent->setDestRect({ destRect.x, destRect.y, destRect.w , CROUCH_HEIGHT });
					SDL_Rect rect = { collisionComponent->getCollider().x, collisionComponent->getCollider().y, collisionComponent->getCollider().w, CROUCH_HEIGHT };
					collisionComponent->setCollider(rect);
					Vector v = { positionComponent->getPos().x, positionComponent->getPos().y + STAND_HEIGHT - CROUCH_HEIGHT };
					positionComponent->setPos(v);
				}
				else
				{
					SDL_Rect destRect = graphicsComponent->getDestRect();
					graphicsComponent->setDestRect({ destRect.x, destRect.y, destRect.w , STAND_HEIGHT });
					SDL_Rect rect = { collisionComponent->getCollider().x, collisionComponent->getCollider().y, collisionComponent->getCollider().w, STAND_HEIGHT };
					collisionComponent->setCollider(rect);
				}

				physicsComponent->setAcceleration(acceleration);
				physicsComponent->setVelocity(velocity);
			}
		}
	}
}
