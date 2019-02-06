#include "ECS/Components/Controller.h"

/// 
/// /// <summary>
/// 
/// </summary>
Controller::Controller() : 
	Up(false),
	Down(false),
	Left(false),
	Right(false),
	Start(false),
	Back(false),
	LeftShoulder(false),
	RightShoulder(false),
	AButton(false),
	BButton(false),
	XButton(false),
	YButton(false),
	StickX(0),
	StickY(0)
{
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

	int MaxJoysticks = SDL_NumJoysticks();
	int ControllerIndex = 0;
	for (int JoystickIndex = 0; JoystickIndex < MaxJoysticks; ++JoystickIndex)
	{
		if (!SDL_IsGameController(JoystickIndex))
		{
			m_controller = SDL_GameControllerOpen(JoystickIndex);
			continue;
		}
		if (ControllerIndex >= MAX_CONTROLLERS)
		{
			break;
		}
		ControllerHandles[ControllerIndex] = SDL_GameControllerOpen(JoystickIndex);
		ControllerIndex++;
	}
}

Controller::~Controller()
{

}

void Controller::update(SDL_Event e)
{
	SDL_Event e;
										//While application is running.
		//Handle events on queue.
		while (SDL_PollEvent(&e) != 0)
		{

			for (int ControllerIndex = 0;
				ControllerIndex < MAX_CONTROLLERS;
				++ControllerIndex)
			{

				if (ControllerHandles[ControllerIndex] != 0 && SDL_GameControllerGetAttached(ControllerHandles[ControllerIndex]))
				{
					// NOTE: We have a controller with index ControllerIndex.
					Up = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_UP);
					Down = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_DOWN);
					Left = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_LEFT);
					Right = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
					Start = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_START);
					Back = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_BACK);
					LeftShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
					RightShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
					AButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_A);
					BButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_B);
					XButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_X);
					YButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex], SDL_CONTROLLER_BUTTON_Y);

					StickX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTX);
					StickY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex], SDL_CONTROLLER_AXIS_LEFTY);
				}
			}

			if (AButton == false)
			{
				std::cout << "A button" << std::endl;
			}


		}
}