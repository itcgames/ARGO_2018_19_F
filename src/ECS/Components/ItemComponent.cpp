#include "ECS\Components\ItemComponent.h"

/// <summary>
/// 
/// </summary>
ItemComponent::ItemComponent() :
	m_isPlaced(false)
{
	m_id = "ITEM";
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool ItemComponent::isPlaced()
{
	return m_isPlaced;
}



/// <summary>
/// 
/// </summary>
/// <param name="isPlaced"></param>
void ItemComponent::setPlaced(bool isPlaced)
{
	m_isPlaced = isPlaced;
}
