#pragma once
#ifndef CONTROLLER
#define CONTROLLER
#define MAX_CONTROLLERS 4

#include<string>
#include<SDL_gamecontroller.h>
#include "SDL2_Helper/SDL2Helper.h"
#include<iostream>

class Controller
{

public:
	Controller();
	~Controller();
	void update(SDL_Event e);
private:
	SDL_GameController *m_controller;
	SDL_GameController *ControllerHandles[MAX_CONTROLLERS];

	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Start;
	bool Back;
	bool LeftShoulder;
	bool RightShoulder;
	bool AButton;
	bool BButton;
	bool XButton;
	bool YButton;

	int StickX;
	int StickY;
};
#endif // !CONTROLLER
