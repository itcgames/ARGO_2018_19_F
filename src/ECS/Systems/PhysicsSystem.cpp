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
		CollisionComponent* collisionComponent = (CollisionComponent*)entity->getComponent("COLLISION");
		GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("PHYSICS");
		

		if (physicsComponent != nullptr && positionComponent != nullptr && entity->getId() != "cursor")
		{
			Vector acceleration = physicsComponent->getAcceleration();
			Vector velocity = physicsComponent->getVelocity();
			Vector friction = physicsComponent->getFriction();
			Vector position = positionComponent->getPos();
			Vector collider = positionComponent->getPos();

			if (physicsComponent->getGravity())
			{
				acceleration += GRAVITY;
			}

			velocity += acceleration * dt;

			if (physicsComponent->getJumping() == false)
			{
				velocity *= friction;
				position += velocity;
			}
			else
			{
				velocity.x *= (friction.x/1.25);
				velocity.y *= friction.y;
				position += velocity;
			}
			
			keepOnScreen(position, velocity, collisionComponent->getCollider(), physicsComponent);
			physicsComponent->setVelocity(velocity);
			positionComponent->setPos(position);

			acceleration = Vector();
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
void PhysicsSystem::keepOnScreen(Vector& position, Vector& velocity, SDL_Rect& dimensions, PhysicsComponent* physics)
{
	if (position.x + dimensions.x> 1600.f)
	{
		position.x = 1600.f - dimensions.w;
		velocity.x = 0;
	}
	if (position.x < 0)
	{
		position.x = 0;
		velocity.x = 0;
	}
	if (position.y + dimensions.h > 900.f)
	{

		position.y = 900.f - dimensions.h;
		physics->setJumping(false);
		velocity.y = 0;
	}
	if (position.y < 0)
	{
		position.y = 0;
		velocity.y = 0;
	}
}
