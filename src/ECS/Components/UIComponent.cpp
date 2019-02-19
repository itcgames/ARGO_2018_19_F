#include "ECS\Components\UIComponent.h"

/// <summary>
/// 
/// </summary>
UIComponent::UIComponent(int order, bool selected) :
	m_order(order),
	m_selected(selected)
{
	m_id = "UI";
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int UIComponent::getOrder()
{
	return m_order;
}



/// <summary>
/// 
/// </summary>
/// <param name="order"></param>
void UIComponent::setOrder(int order)
{
	m_order = order;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool UIComponent::isSelected()
{
	return m_selected;
}



/// <summary>
/// 
/// </summary>
/// <param name="selected"></param>
void UIComponent::setSelected(bool selected)
{
	m_selected = selected;
}
