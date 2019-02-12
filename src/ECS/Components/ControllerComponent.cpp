#include "ECS/Components/ControllerComponent.h"

int ControllerComponent::m_controllerIndex = 0;

/// <summary>
/// 
/// </summary>
ControllerComponent::ControllerComponent(int index)
{    
	m_id = "CONTROLLER";
	if (index == -1)
	{
		m_controller = SDL_GameControllerOpen(m_controllerIndex);
		m_controllerIndex++;
	}
	else
	{
		m_controller = SDL_GameControllerOpen(index);
	}
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
ControllerState & ControllerComponent::getCurrentState()
{
	m_previousState = m_currentState;

	//  D-pad.
	m_currentState.dpadUp = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	m_currentState.dpadDown = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	m_currentState.dpadLeft = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	m_currentState.dpadRight = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	//  Centre buttons.
	m_currentState.start = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_START);
	m_currentState.back = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_BACK);
	//  Shoulder buttons.
	m_currentState.leftShoulder = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	m_currentState.rightShoulder = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	//  Face buttons.
	m_currentState.A = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_A);
	m_currentState.B = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_B);
	m_currentState.X = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_X);
	m_currentState.Y = SDL_GameControllerGetButton(m_controller, SDL_CONTROLLER_BUTTON_Y);
	//  Sticks.
	m_currentState.leftStick = Vector(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);
	m_currentState.rightStick = Vector(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_RIGHTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_RIGHTY) / MAX_STICK_VALUE);
	//	Triggers.
	m_currentState.leftTrigger = SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / MAX_TRIGGER_VALUE;
	m_currentState.rightTrigger = SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / MAX_TRIGGER_VALUE;

	return m_currentState;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
ControllerState & ControllerComponent::getPreviousState()
{
	return m_previousState;
}
