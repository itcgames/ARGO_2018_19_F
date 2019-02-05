#include "ECS/Components/Controller.h"

/// 
/// /// <summary>
/// 
/// </summary>
Controller::Controller()
{
	m_controller = nullptr;
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			m_controller = SDL_GameControllerOpen(i);
			break;
		}
	}
}

Controller::~Controller()
{

}

void Controller::update()
{
	bool quit = false;
	SDL_Event e;
	Uint64 LAST;
	Uint64 NOW = SDL_GetPerformanceCounter();

										//While application is running.
	while (!quit)
	{
		//Handle events on queue.
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit.
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			else if (e.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					std::cout << "x pressed" << std::endl;
				}
			}

			else if (e.type == SDL_CONTROLLERAXISMOTION)
			{
				if (e.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
				{
					std::cout << SDL_CONTROLLER_AXIS_TRIGGERRIGHT << std::endl;
				}
			}
			else if (e.type == SDL_JOYAXISMOTION)
			{
				if (e.caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
				{
					std::cout << SDL_JoystickGetAxis << std::endl;
				}
			}
		}
	}
}