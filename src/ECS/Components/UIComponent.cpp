#include "ECS\Components\UIComponent.h"

/// <summary>
/// 
/// </summary>
UIComponent::UIComponent(int index, bool selected, std::string goTo, Texture normalTexture, Texture highlightedTexture, Texture pressedTexture) :
	m_index(index),
	m_selected(selected),
	m_goTo(goTo),
	m_normalTexture(normalTexture),
	m_highlightedTexture(highlightedTexture),
	m_pressedTexture(pressedTexture)
{
	m_id = "UI";
	m_texture = normalTexture;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int UIComponent::getIndex()
{
	return m_index;
}



/// <summary>
/// 
/// </summary>
/// <param name="order"></param>
void UIComponent::setIndex(int index)
{
	m_index = index;
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



/// <summary>
/// 
/// </summary>
/// <param name="state"></param>
void UIComponent::setState(ButtonStates state)
{
	switch (state)
	{
	case ButtonStates::Up:
		m_texture = m_normalTexture;
		break;
	case ButtonStates::Pressed:
		m_texture = m_pressedTexture;
		break;
	case ButtonStates::Highlighted:
		m_texture = m_highlightedTexture;
		break;
	default:
		m_texture = m_normalTexture;
		break;
	}
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Texture UIComponent::getTexture()
{
	return m_texture;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string UIComponent::getGoTo()
{
	return m_goTo;
}
