#include "ECS/Systems/AICursorControlSystem.h"
#include <stdlib.h>



AICursorControlSystem::AICursorControlSystem()
{
}


AICursorControlSystem::~AICursorControlSystem()
{
}

/// <summary>
/// Test method for placement AI
/// Here's hoping
/// </summary>
/// <param name="dt"></param>
/// <param name="picking"></param>
void AICursorControlSystem::update(double dt, bool picking)
{
	float x = 800;
	float y = 800;

	//x = rand() % 1600;
	//y = rand() % 900;

	Vector v = { x,y };
	Vector vAdd = { 0.5f,0.5f };

	bool pick = true;

	for (Entity* entity1 : m_entities)
	{
		CollisionComponent* collision1 = (CollisionComponent*)entity1->getComponent("COLLISION");
		PositionComponent* position1 = (PositionComponent*)entity1->getComponent("POSITION");

		for (Entity* entity2 : m_entities)
		{

			CollisionComponent* collision2 = (CollisionComponent*)entity2->getComponent("COLLISION");
			PositionComponent* position2 = (PositionComponent*)entity2->getComponent("POSITION");
			PlacedComponent* placed = (PlacedComponent*)entity2->getComponent("PLACED");

			if (pick)
			{
				if (entity1->getId() == "AI_cursor" && entity2 ->getId() == "platMove")
				{
					if (placed->getPlaced() == false)
					{
							position1->setPos(position2->getPos());
							
							while (position2->getPos().x < v.x)
							{
								Vector newVec = { position2->getPos().x + vAdd.y, position2->getPos().y + vAdd.y };
								//position2->setPos(newVec);
							}
							//position2->setPos(v);
							placed->setPlaced();

							//std::cout << position1


					}
						
				}
			}
		}
	}
}
