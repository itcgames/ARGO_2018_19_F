#include "ECS/Components/ControllerComponent.h"

/// <summary>
/// 
/// </summary>
ControllerComponent::ControllerComponent()
{
	m_id = "CONTROLLER";
	m_controller = SDL_GameControllerOpen(0);

	int MaxJoysticks = SDL_NumJoysticks();
	int ControllerIndex = 0;
	for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
	{
		if (!SDL_IsGameController(JoystickIndex))
		{
			m_controller = SDL_GameControllerOpen(JoystickIndex);
		}
	}
}
