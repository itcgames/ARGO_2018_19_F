#include "ECS/Systems/PhysicsSystem.h"

/// <summary>
/// update loop for applying phsyics to components
/// </summary>
/// <param name="dt"></param>
void PhysicsSystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
		ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");

		if (physicsComponent != nullptr && positionComponent != nullptr)
		{
			Vector acceleration = physicsComponent->getAcceleration();
			Vector velocity = physicsComponent->getVelocity();
			Vector friction = physicsComponent->getFriction();
			if (physicsComponent->getGravity())
			{
				acceleration += m_gravity;
			}

			velocity += acceleration * dt;
			velocity.x *= friction.x;

			Vector position = *positionComponent->getPos();
			position += velocity;
			if (position.y > 768.f)
			{
				controllerComponent->m_isJumping = false;
				position.y = 768.f;
				velocity.y = m_gravity.y;
			}
			Vector size = Vector (32, 32);
			keepOnScreen(position, velocity, size);
			physicsComponent->setVelocity(velocity);
			positionComponent->setPos(position);

			acceleration = Vector(0, 0, 0);
			physicsComponent->setAcceleration(acceleration);
		}
	}
}

void PhysicsSystem::keepOnScreen(Vector& position, Vector& velocity, Vector& dimensions)
{
	if (position.x + dimensions.x> 1600.f)
	{
		position.x = 1600.f - dimensions.x;
		velocity.x = 0;
	}
	if (position.x < 0)
	{
		position.x = 0;
		velocity.x = 0;
	}
}
