#include "ECS/Components/PlacedComponent.h"

/// <summary>
/// 
/// </summary>
PlacedComponent::PlacedComponent(bool placed) :
	m_placed(placed)
{
	m_id = "PLACED";
}



/// <summary>
/// 
/// </summary>
void PlacedComponent::setPlaced()
{
	m_placed = !m_placed;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool PlacedComponent::getPlaced()
{
	return m_placed;
}