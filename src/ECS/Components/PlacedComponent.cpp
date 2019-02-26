#include "ECS/Components/PlacedComponent.h"



PlacedComponent::PlacedComponent()
{
	m_id = ("PLACED");
}


PlacedComponent::~PlacedComponent()
{
}

void PlacedComponent::setPlaced()
{
	m_placed = !m_placed;
}

bool PlacedComponent::getPlaced()
{
	return m_placed;
}