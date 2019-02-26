#include "ECS/Systems/SelectionBoxSystem.h"

/// <summary>
///  A loop for updating the physics of the 
///  pause / score / selection screen
/// </summary>
void SelectionBoxSystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		SelectionBoxComponent* selectionBox = (SelectionBoxComponent*)entity->getComponent("SELECTION_BOX");
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		
		if (selectionBox != nullptr && positionComponent != nullptr)
		{
			if (selectionBox->isVisible())
			{
				if (positionComponent->getPos().y <= -10)
				{
					Vector v = { positionComponent->getPos().x, positionComponent->getPos().y + 20 };
					positionComponent->setPos(v);
				}
			}
			else
			{
				if (positionComponent->getPos().y >= -1000)
				{
					Vector v = { positionComponent->getPos().x, positionComponent->getPos().y - 100 };
					positionComponent->setPos(v);
				}
			}
		}
	}
}
