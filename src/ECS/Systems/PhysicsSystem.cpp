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

			Vector size = Vector(32, 32);
			if (position.y + size.y > 900.f)
			{
				controllerComponent->m_isJumping = false;
				position.y = 900.f - size.y;
				velocity.y = m_gravity.y;
			}
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
