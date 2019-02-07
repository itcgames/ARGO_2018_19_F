#include "ECS\Systems\CollisionSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void CollisionSystem::update(double dt)
{
	for (Entity* entity1 : m_entities)
	{
		PositionComponent* e1Position = (PositionComponent*)entity1->getComponent("POSITION");
		CollisionComponent* e1Collision = (CollisionComponent*)entity1->getComponent("COLLISION");
		e1Collision->setIsColliding(false);

		for (Entity* entity2 : m_entities)
		{
			PositionComponent* e2Position = (PositionComponent*)entity2->getComponent("POSITION");
			CollisionComponent* e2Collision = (CollisionComponent*)entity2->getComponent("COLLISION");

			if (entity1 != entity2)
			{
				if (e1Position->getPos()->x <= e2Position->getPos()->x + e2Collision->getCollider().w &&
					e1Position->getPos()->x + e1Collision->getCollider().w >= e2Position->getPos()->x &&
					e1Position->getPos()->y <= e2Position->getPos()->y + e2Collision->getCollider().h &&
					e1Position->getPos()->y + e1Collision->getCollider().h >= e2Position->getPos()->y)
				{
					if (!e1Collision->IsColliding())
					{
						if (e1Collision->m_tag == "Player")
						{
							e1Collision->setIsColliding(true);

							// collision direction
							Vector e1Centre = Vector(e1Position->getPos()->x - e1Collision->getCollider().w / 2, e1Position->getPos()->y - e1Collision->getCollider().h / 2);
							Vector e2Centre = Vector(e2Position->getPos()->x - e2Collision->getCollider().w / 2, e2Position->getPos()->y - e2Collision->getCollider().h / 2);
							Vector collisionResponse = Vector(e1Centre.x - e2Centre.x, e1Centre.y - e2Centre.y);
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");

							if (collisionResponse.y > 0)
							{
								Vector newPos = Vector(e1Position->getPos()->x, e2Position->getPos()->y + e2Collision->getCollider().h);
								e1Position->setPos(newPos);
								Vector newV = Vector(physicsComponent->getVelocity().x, 0, 0);
								physicsComponent->setVelocity(newV);
							}
							if (collisionResponse.y < 0)
							{
								Vector newPos = Vector(e1Position->getPos()->x, e2Position->getPos()->y - e2Collision->getCollider().h);
								e1Position->setPos(newPos);
								Vector newV = Vector(physicsComponent->getVelocity().x, 0, 0);
								physicsComponent->setVelocity(newV);
							}
							if (collisionResponse.x > 0 && collisionResponse.y > 0)
							{
								Vector newPos = Vector(e2Position->getPos()->x + e2Collision->getCollider().w, e1Position->getPos()->y);
								e1Position->setPos(newPos);
								Vector newV = Vector(0, physicsComponent->getVelocity().y, 0);
								physicsComponent->setVelocity(newV);
							}
							if (collisionResponse.x < 0 && collisionResponse.y > 0)
							{
								Vector newPos = Vector(e1Centre.x - e1Collision->getCollider().w / 2, e1Position->getPos()->y);
								e1Position->setPos(newPos);
								Vector newV = Vector(0, physicsComponent->getVelocity().y, 0);
								physicsComponent->setVelocity(newV);
							}
						}
					}
				}
			}
		}
	}
}
