#include "ECS/Components/AIComponent.h"

AIComponent::AIComponent()
{
	m_id = "AI";
	m_onGround = false;
	m_onPlatform = false;
}

void AIComponent::setGridLocation(int i, int j)
{
	m_gridLocation = Vector(i, j);
}

Vector & AIComponent::getGridLocation()
{
	return m_gridLocation;
}
