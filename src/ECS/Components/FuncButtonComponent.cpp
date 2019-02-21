#include "ECS\Components\FuncButtonComponent.h"

/// <summary>
/// 
/// </summary>
/// <param name="index"></param>
/// <param name="selected"></param>
/// <param name="function"></param>
FuncButtonComponent::FuncButtonComponent(int index, bool selected, std::function<void()> function, SDL_Rect defaultRect) :
	m_index(index),
	m_selected(selected),
	m_function(function),
	m_defaultRect(defaultRect)
{
	m_id = "FUNC_BUTTON";

	m_destRect = defaultRect;
	m_scaledRect = {0, 0, defaultRect.w + 10,  defaultRect.h + 10 };
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int FuncButtonComponent::getIndex()
{
	return m_index;
}



/// <summary>
/// 
/// </summary>
/// <param name="index"></param>
void FuncButtonComponent::setIndex(int index)
{
	m_index = index;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool FuncButtonComponent::isSelected()
{
	return m_selected;
}



/// <summary>
/// 
/// </summary>
/// <param name="selected"></param>
void FuncButtonComponent::setSelected(bool selected)
{
	m_selected = selected;
}



/// <summary>
/// 
/// </summary>
void FuncButtonComponent::callFunction()
{
	m_function();
}



/// <summary>
/// 
/// </summary>
/// <param name="state"></param>
void FuncButtonComponent::setButtonState(FuncButtonStates state)
{
	switch (state)
	{
	case FuncButtonStates::Selected:
		m_destRect = m_scaledRect;
		break;
	case FuncButtonStates::NotSelected:
		m_destRect = m_defaultRect;
		break;
	default:
		break;
	}
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
SDL_Rect FuncButtonComponent::getDestRect()
{
	return m_destRect;
}
