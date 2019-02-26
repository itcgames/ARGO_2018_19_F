#include "ECS/Systems/AICursorControlSystem.h"



AICursorControlSystem::AICursorControlSystem()
{
}


AICursorControlSystem::~AICursorControlSystem()
{
}

void AICursorControlSystem::update(double dt, bool picking)
{
	bool pick = true;

	for (Entity* entity1 : m_entities)
	{
		CollisionComponent* collision1 = (CollisionComponent*)entity1->getComponent("COLLISION");
		PositionComponent* position1 = (PositionComponent*)entity1->getComponent("POSITION");

		for (Entity* entity2 : m_entities)
		{

			CollisionComponent* collision2 = (CollisionComponent*)entity2->getComponent("COLLISION");
			PositionComponent* position2 = (PositionComponent*)entity2->getComponent("POSITION");

			if (pick)
			{
				if (entity1->getId() == "AIcursor" && entity2 ->getId() == "Platform")
				{
					if (entity2)
					{
						position1->setPos(position2->getPos());
					}
				}
			}
		}
	}
}
