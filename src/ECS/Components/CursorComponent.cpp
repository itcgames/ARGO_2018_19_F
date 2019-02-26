#include "ECS\Components\CursorComponent.h"

/// <summary>
/// 
/// </summary>
CursorComponent::CursorComponent()
{
	m_id = "CURSOR";
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool CursorComponent::isActive()
{
	return m_active;
}



/// <summary>
/// 
/// </summary>
/// <param name="active"></param>
void CursorComponent::setIsActive(bool active)
{
	m_active = active;
}



/// <summary>
/// 
/// </summary>
void CursorComponent::flipActive()
{
	m_active = !m_active;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool CursorComponent::isHoldingObject()
{
	return m_holdingObject;
}



/// <summary>
/// 
/// </summary>
/// <param name="holdingObject"></param>
void CursorComponent::setIsHoldingObject(bool holdingObject)
{
	m_holdingObject = holdingObject;
}



/// <summary>
/// 
/// </summary>
void CursorComponent::flipHoldingObject()
{
	m_holdingObject = !m_holdingObject;
}
