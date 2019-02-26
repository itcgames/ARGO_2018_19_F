#include "ECS/Components/SelectionBoxComponent.h"

/// <summary>
/// 
/// </summary>
SelectionBoxComponent::SelectionBoxComponent(bool isVisible) :
	m_visible(isVisible)
{
	m_id = "SELECTION_BOX";
}



/// <summary>
/// 
/// </summary>
SelectionBoxComponent::~SelectionBoxComponent()
{

}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool SelectionBoxComponent::isVisible()
{
	return m_visible;
}



/// <summary>
/// 
/// </summary>
/// <param name="isVisible"></param>
void SelectionBoxComponent::setIsVisible(bool isVisible)
{
	m_visible = isVisible;
}
