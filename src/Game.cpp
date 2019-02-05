#include "Game.h"
//#include<SDL_gamecontroller.h>
#include<iostream>

/// <summary>
/// 
/// </summary>
Game::Game() :
	m_window(SDL_CreateWindow("ARGO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 900, 0)),
	m_renderer(SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
{
	//	Set the default draw colour.
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
	
	//	Add all the screens to the screen manager, and then set the current screen.
	m_screenManager.addScreen(new Splash());
	m_screenManager.addScreen(new Title());
	m_screenManager.addScreen(new Menu());
	m_screenManager.addScreen(new LevelSelect());
	m_screenManager.addScreen(new CharacterSelect());
	m_screenManager.addScreen(new Play());
	m_screenManager.addScreen(new Settings());
	m_screenManager.addScreen(new Credits());

	m_screenManager.goToScreen("Play");

	SDL_GameController *m_controller;
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



/// <summary>
/// 
/// </summary>
Game::~Game()
{

}



/// <summary>
/// 
/// </summary>
void Game::run()
{
	bool quit = false;
	SDL_Event e;
	Uint64 LAST;
	Uint64 NOW = SDL_GetPerformanceCounter();
	double deltaTime;
	short fps = 60;
	short timePerFrame = 1000 / fps;	// The time per frame = 1000ms / fps

	//While application is running.
	while (!quit)
	{
		//Handle events on queue.
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit.
			if (e.type == SDL_QUIT)
			{
				//	Destroy window.
				SDL_DestroyRenderer(m_renderer);
				m_renderer = NULL;
				SDL_DestroyWindow(m_window);
				m_window = NULL;

				//	Exit SDL.
				IMG_Quit();
				SDL_Quit();

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

		//	Calculate deltaTime.
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = ((double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()));

		if (timePerFrame > deltaTime)
		{
			SDL_Delay(timePerFrame - deltaTime);
		}
		else if (timePerFrame < deltaTime)
		{
			fps = 1000 / deltaTime;
		}

		//	Call game functions.
		update(deltaTime);
		render();
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Game::update(double dt)
{
	m_screenManager.update(dt);
}



/// <summary>
/// 
/// </summary>
void Game::render()
{
	//	Clear the screen.
	SDL_RenderClear(m_renderer);

	m_screenManager.render(m_renderer);

	//	Update screen.
	SDL_RenderPresent(m_renderer);
}