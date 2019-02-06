#include "ECS/Components/Controller.h"

/// 
/// /// <summary>
/// 
/// </summary>
Controller::Controller() 
{
	m_id = "CONTROLLER";
	m_controller = nullptr;
	/*for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			m_controller = SDL_GameControllerOpen(i);
			break;
		}

		ControllerHandles[i] = SDL_GameControllerOpen(i);
	}*/
	//m_controller = new SDL_GameController();

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
