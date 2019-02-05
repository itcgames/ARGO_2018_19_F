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

			if (Up == true)
			{
				std::cout << "UP" << std::endl;
			}
	}
}