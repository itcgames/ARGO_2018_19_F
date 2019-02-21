#include "ECS/Systems/UIControlSystem.h"

UIControlSystem::UIControlSystem(ScreenManager * screenManager) :
	m_screenManager(screenManager),
	m_initialised(false)
{
}



/// <summary>
/// 
/// </summary>
void UIControlSystem::initSystem()
{
	updateMinMax();
	ButtonComponent* buttonComponent = (ButtonComponent*)m_entities[m_selected]->getComponent("BUTTON");
	if (buttonComponent != nullptr)
	{
		buttonComponent->setState(ButtonStates::Highlighted);
	}	
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void UIControlSystem::update(double dt)
{
	if (!m_initialised)
	{
		initSystem();
		m_initialised = true;
	}

	ButtonComponent* buttonComponent = (ButtonComponent*)m_entities[m_selected]->getComponent("BUTTON");
	FuncButtonComponent* funcButtonComponent = (FuncButtonComponent*)m_entities[m_selected]->getComponent("FUNC_BUTTON");
	ControllerComponent* controllerComponent = (ControllerComponent*)m_entities[m_selected]->getComponent("CONTROLLER");	

	//	If the button just switches the screen of the game.
	if (buttonComponent != nullptr)
	{
		//	Set m_selected to the index of the selected ui element.
		if (!buttonComponent->isSelected() && m_selected == buttonComponent->getIndex())
		{
			m_selected = buttonComponent->getIndex();
			buttonComponent->setSelected(true);
			buttonComponent->setState(ButtonStates::Highlighted);
		}

		updateTextures();

		if (controllerComponent != nullptr)
		{
			m_currentState = controllerComponent->getCurrentState();					

			//	If the left stick is pushed up move the selected value back one.
			if (m_currentState.leftStick.y < -controllerComponent->DEAD_ZONE && m_previousState.leftStick.y > -controllerComponent->DEAD_ZONE)
			{
				//	Update which is selected.
				buttonComponent->setSelected(false);
				buttonComponent->setState(ButtonStates::Up);
				//	Update the selected value.
				m_selected--;
				clampSelected();				
			}

			//	If the left stick is push down move the selected value forward one.
			if (m_currentState.leftStick.y > controllerComponent->DEAD_ZONE && m_previousState.leftStick.y < controllerComponent->DEAD_ZONE)
			{
				//	Update which is selected.
				buttonComponent->setSelected(false);
				buttonComponent->setState(ButtonStates::Up);
				//	Update the selected value.
				m_selected++;
				clampSelected();				
			}

			if (m_currentState.A && !m_previousState.A)
			{
				buttonComponent->setState(ButtonStates::Pressed);
			}

			if (!m_currentState.A && m_previousState.A)
			{
				buttonComponent->setState(ButtonStates::Highlighted);
				m_screenManager->goToScreen(buttonComponent->getGoTo());
			}

			if (!m_currentState.B && m_previousState.B)
			{
				m_screenManager->backToPrevious();
			}			

			m_previousState = m_currentState;
		}		
	}
	//	If the button needs to call a function on press.
	else if (funcButtonComponent != nullptr)
	{
		//	Set m_selected to the index of the selected ui element.
		if (!funcButtonComponent->isSelected() && m_selected == funcButtonComponent->getIndex())
		{
			m_selected = funcButtonComponent->getIndex();
			funcButtonComponent->setSelected(true);
			funcButtonComponent->setButtonState(FuncButtonStates::Selected);
		}

		updateTextures();

		if (controllerComponent != nullptr)
		{
			m_currentState = controllerComponent->getCurrentState();

			//	If the left stick is pushed up move the selected value back one.
			if (m_currentState.leftStick.y < -controllerComponent->DEAD_ZONE && m_previousState.leftStick.y > -controllerComponent->DEAD_ZONE)
			{
				//	Update which is selected.
				funcButtonComponent->setSelected(false);
				funcButtonComponent->setButtonState(FuncButtonStates::NotSelected);
				//	Update the selected value.
				m_selected--;
				clampSelected();
			}

			//	If the left stick is push down move the selected value forward one.
			if (m_currentState.leftStick.y > controllerComponent->DEAD_ZONE && m_previousState.leftStick.y < controllerComponent->DEAD_ZONE)
			{
				//	Update which is selected.
				funcButtonComponent->setSelected(false);
				funcButtonComponent->setButtonState(FuncButtonStates::NotSelected);
				//	Update the selected value.
				m_selected++;
				clampSelected();
			}

			if (!m_currentState.A && m_previousState.A)
			{
				funcButtonComponent->callFunction();
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
		ButtonComponent* buttonComponent = (ButtonComponent*)entity->getComponent("BUTTON");
		if (buttonComponent != nullptr)
		{
			if (buttonComponent->getIndex() < m_min)
			{
				m_min = buttonComponent->getIndex();
			}

			if (buttonComponent->getIndex() > m_max)
			{
				m_max = buttonComponent->getIndex();
			}
		}

		FuncButtonComponent* funcButtonComponent = (FuncButtonComponent*)entity->getComponent("FUNC_BUTTON");
		if (funcButtonComponent != nullptr)
		{
			if (funcButtonComponent->getIndex() < m_min)
			{
				m_min = funcButtonComponent->getIndex();
			}

			if (funcButtonComponent->getIndex() > m_max)
			{
				m_max = funcButtonComponent->getIndex();
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
		if (graphicsComponent != nullptr)
		{
			ButtonComponent* buttonComponent = (ButtonComponent*)entity->getComponent("BUTTON");
			if (buttonComponent != nullptr)
			{
				Texture texture = buttonComponent->getTexture();
				graphicsComponent->setTexture(texture.texture);
				graphicsComponent->setSourceRect(texture.srcRect);
			}

			FuncButtonComponent* funcButtonComponent = (FuncButtonComponent*)entity->getComponent("FUNC_BUTTON");
			if (funcButtonComponent != nullptr)
			{
				graphicsComponent->setDestRect(funcButtonComponent->getDestRect());
			}
		}
	}
}
