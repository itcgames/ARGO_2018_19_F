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
	
	if (random == false)
	{
		x = rand() % 1400 + 100;
		y = rand() % 700 + 100;
		random = true;
	}


	Vector v = { x,y };
	Vector vAdd = { 5.0f,5.0f };

	bool pick = true;

	for (Entity* entity1 : m_entities)
	{
		CollisionComponent* collision1 = (CollisionComponent*)entity1->getComponent("COLLISION");
		PositionComponent* position1 = (PositionComponent*)entity1->getComponent("POSITION");
		PlacedComponent* placed = (PlacedComponent*)entity1->getComponent("PLACED");

		for (Entity* entity2 : m_entities)
		{

			CollisionComponent* collision2 = (CollisionComponent*)entity2->getComponent("COLLISION");
			PositionComponent* position2 = (PositionComponent*)entity2->getComponent("POSITION");
			

			if (pick)
			{
				if (entity1->getId() == "AI_cursor" && entity2 ->getId() == "platform")
				{
					if (placed->getPlaced() == false)
					{
							position1->setPos(position2->getPos());
							
							if (position2->getPos().x <= v.x - 5 || position2->getPos().x >= v.x + 5 && m_right == false)
							{
								if (position2->getPos().x < v.x)
								{
									Vector newVec = { position2->getPos().x + vAdd.x, position2->getPos().y };
									position2->setPos(newVec);
									position1->setPos(newVec);
								}
								else if (position2->getPos().x > v.x)
								{
									Vector newVec = { position2->getPos().x - vAdd.x, position2->getPos().y };
									position2->setPos(newVec);
									position1->setPos(newVec);
								}
								
							}
							else
							{
								m_right = true;
							}
							if ((position2->getPos().y <= v.y + 1 || position2->getPos().y >= v.y - 1) && m_right == true)
							{
								 if (position2->getPos().y < v.y)
								{
									Vector newVec = { position2->getPos().x, position2->getPos().y + vAdd.y };
									position2->setPos(newVec);
									position1->setPos(newVec);
								}
								else if (position2->getPos().y > v.y)
								{
									Vector newVec = { position2->getPos().x, position2->getPos().y - vAdd.y };
									position2->setPos(newVec);
									position1->setPos(newVec);
								}
							}

							 if (position2->getPos().x <= v.x + 5 && position2->getPos().x >= v.x - 5 && position2->getPos().y <= v.y + 5 && position2->getPos().y >= v.y - 5)
							{
								placed->setPlaced();
								random = false;
								m_right = false;
							}
							//std::cout << position1


					}
						
				}
				else if (entity1->getId() == "AI_cursor" && entity2->getId() == "obstacle")
				{
					if (placed->getPlaced() == false)
					{
						position1->setPos(position2->getPos());

						if (position2->getPos().x <= v.x - 5 || position2->getPos().x >= v.x + 5 && m_right == false)
						{
							if (position2->getPos().x < v.x)
							{
								Vector newVec = { position2->getPos().x + vAdd.x, position2->getPos().y };
								position2->setPos(newVec);
								position1->setPos(newVec);
							}
							else if (position2->getPos().x > v.x)
							{
								Vector newVec = { position2->getPos().x - vAdd.x, position2->getPos().y };
								position2->setPos(newVec);
								position1->setPos(newVec);
							}

						}
						else
						{
							m_right = true;
						}
						if ((position2->getPos().y <= v.y + 1 || position2->getPos().y >= v.y - 1) && m_right == true)
						{
							if (position2->getPos().y < v.y)
							{
								Vector newVec = { position2->getPos().x, position2->getPos().y + vAdd.y };
								position2->setPos(newVec);
								position1->setPos(newVec);
							}
							else if (position2->getPos().y > v.y)
							{
								Vector newVec = { position2->getPos().x, position2->getPos().y - vAdd.y };
								position2->setPos(newVec);
								position1->setPos(newVec);
							}
						}

						if (position2->getPos().x <= v.x + 5 && position2->getPos().x >= v.x - 5 && position2->getPos().y <= v.y + 5 && position2->getPos().y >= v.y - 5)
						{
							placed->setPlaced();
							random = false;
							m_right = false;
						}
						//std::cout << position1


					}

				}
			}
		}
	}
}
