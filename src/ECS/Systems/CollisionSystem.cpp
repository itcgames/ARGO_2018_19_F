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
				if (e1Position->getPos()->x <= e2Position->getPos()->x + e1Collision->getCollider().w &&
					e1Position->getPos()->x + e1Collision->getCollider().w >= e2Position->getPos()->x &&
					e1Position->getPos()->y <= e2Position->getPos()->y + e1Collision->getCollider().h &&
					e1Position->getPos()->y + e1Collision->getCollider().h >= e2Position->getPos()->y)
				{
					if (!e1Collision->IsColliding())
					{
						e1Collision->setIsColliding(true);
					}
				}
			}
		}
	}
}
