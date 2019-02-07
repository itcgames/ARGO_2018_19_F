#include "ECS/Components/ControllerComponent.h"

int ControllerComponent::m_controllerIndex = 0;

/// <summary>
/// 
/// </summary>
ControllerComponent::ControllerComponent()
{    
	m_id = "CONTROLLER";
	m_isJumping = true;
	m_controller = SDL_GameControllerOpen(m_controllerIndex);
    m_controllerIndex++;
}
