#include "ECS/Systems/ObjectPlacedSystem.h"



ObjectPlacedSystem::ObjectPlacedSystem()
{
}


ObjectPlacedSystem::~ObjectPlacedSystem()
{
}

/// <summary>
/// update for finding placed componenet
/// </summary>
void ObjectPlacedSystem::update()
{
	m_placed = 0;
	for (Entity* entity : m_entities)
	{
		PlacedComponent* placed = (PlacedComponent*)entity->getComponent("PLACED");
		if (placed->getPlaced() == true)
		{
			m_placed++;
		}
	}
}


int ObjectPlacedSystem::getNumberOfObjectsPlaced()
{
	return m_placed;
}