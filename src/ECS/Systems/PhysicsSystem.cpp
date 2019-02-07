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
			Vector position = positionComponent->getPos();

			if (physicsComponent->getGravity())
			{
				acceleration += m_gravity;
			}

			velocity += acceleration * dt;
			velocity *= friction;
			position += velocity;

			Vector size = Vector(32, 32);
			keepOnScreen(position, velocity, size, physicsComponent);
			physicsComponent->setVelocity(velocity);
			positionComponent->setPos(position);

			acceleration = Vector(0, 0, 0);
			physicsComponent->setAcceleration(acceleration);
		}
	}
}



/// <summary>
/// keeps the entity on screen - testing purposes
/// </summary>
/// <param name="position"></param>
/// <param name="velocity"></param>
/// <param name="dimensions"></param>
/// <param name="physics"></param>
void PhysicsSystem::keepOnScreen(Vector& position, Vector& velocity, Vector& dimensions, PhysicsComponent* physics)
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
	if (position.y + dimensions.y > 900.f)
	{

		position.y = 900.f - dimensions.y;
		physics->setJumping(false);
		velocity.y = 0;
	}
	if (position.y < 0)
	{
		position.y = 0;
		velocity.y = 0;
	}
}
