#include "ECS/Systems/UIControlSystem.h"

UIControlSystem::UIControlSystem(ScreenManager * screenManager) :
	m_screenManager(screenManager)
{
}



/// <summary>
/// 
/// </summary>
void UIControlSystem::initSystem()
{
	updateMinMax();
	UIComponent* uiComponent = (UIComponent*)m_entities[m_selected]->getComponent("UI");
	uiComponent->setState(ButtonStates::Highlighted);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void UIControlSystem::update(double dt)
{
	UIComponent* uiComponent = (UIComponent*)m_entities[m_selected]->getComponent("UI");
	ControllerComponent* controllerComponent = (ControllerComponent*)m_entities[m_selected]->getComponent("CONTROLLER");	

	if (uiComponent != nullptr)
	{
		//	Set m_selected to the index of the selected ui element.
		if (!uiComponent->isSelected() && m_selected == uiComponent->getIndex())
		{
			m_selected = uiComponent->getIndex();
			uiComponent->setSelected(true);
			uiComponent->setState(ButtonStates::Highlighted);
		}

		updateTextures();

		if (controllerComponent != nullptr)
		{
			m_currentState = controllerComponent->getCurrentState();					

			//	If the left stick is pushed up move the selected value back one.
			if (m_currentState.leftStick.y < -controllerComponent->DEAD_ZONE && m_previousState.leftStick.y > -controllerComponent->DEAD_ZONE)
			{
				//	Update which is selected.
				uiComponent->setSelected(false);
				uiComponent->setState(ButtonStates::Up);
				//	Update the selected value.
				m_selected--;
				clampSelected();				
			}

			//	If the left stick is push down move the selected value forward one.
			if (m_currentState.leftStick.y > controllerComponent->DEAD_ZONE && m_previousState.leftStick.y < controllerComponent->DEAD_ZONE)
			{
				//	Update which is selected.
				uiComponent->setSelected(false);
				uiComponent->setState(ButtonStates::Up);
				//	Update the selected value.
				m_selected++;
				clampSelected();				
			}

			if (m_currentState.A && !m_previousState.A)
			{
				uiComponent->setState(ButtonStates::Pressed);
			}

			if (!m_currentState.A && m_previousState.A)
			{
				uiComponent->setState(ButtonStates::Highlighted);
				m_screenManager->goToScreen(uiComponent->getGoTo());
			}

			if (!m_currentState.B && m_previousState.B)
			{
				m_screenManager->backToPrevious();
			}

			m_previousState = m_currentState;
		}		
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="index"></param>
void UIControlSystem::updateMinMax()
{
	for (Entity* entity : m_entities)
	{
		UIComponent* uiComponent = (UIComponent*)entity->getComponent("UI");
		if (uiComponent != nullptr)
		{
			if (uiComponent->getIndex() < m_min)
			{
				m_min = uiComponent->getIndex();
			}

			if (uiComponent->getIndex() > m_max)
			{
				m_max = uiComponent->getIndex();
			}
		}
	}
}



/// <summary>
/// 
/// </summary>
void UIControlSystem::clampSelected()
{
	m_selected = m_selected > m_max ? m_max : m_selected;
	m_selected = m_selected < m_min ? m_min : m_selected;
}



/// <summary>
/// 
/// </summary>
void UIControlSystem::updateTextures()
{
	for (Entity* entity : m_entities)
	{
		GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("GRAPHICS");
		UIComponent* uiComponent = (UIComponent*)entity->getComponent("UI");
		Texture texture = uiComponent->getTexture();
		graphicsComponent->setTexture(texture.texture);
		graphicsComponent->setSourceRect(texture.srcRect);
	}
}
