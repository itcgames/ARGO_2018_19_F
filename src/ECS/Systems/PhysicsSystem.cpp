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

		if (physicsComponent != nullptr && positionComponent != nullptr)
		{
			Vector acceleration = physicsComponent->getAcceleration();
			Vector velocity = physicsComponent->getVelocity();
			Vector friction = physicsComponent->getFriction();
			if (physicsComponent->getGravity())
			{
				if (positionComponent->getPos().y < 800.f)
				{
					acceleration += m_gravity;
				}
				else
				{
					// temporary value for testing purposes
					velocity = Vector(0, 0, 0);
				}
			}

			velocity += acceleration * dt;
			physicsComponent->setVelocity(velocity);

			Vector position = positionComponent->getPos();
			position += velocity;
			std::cout << position.x << ", " << position.y << std::endl;
			positionComponent->setPos(position);

			acceleration = Vector(0, 0, 0);
			physicsComponent->setAcceleration(acceleration);
		}
	}
}