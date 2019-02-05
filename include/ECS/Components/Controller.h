#pragma once
#ifndef CONTROLLER
#define CONTROLLER

#include<string>
#include<SDL_gamecontroller.h>
#include "SDL2_Helper/SDL2Helper.h"
#include<iostream>

class Controller
{

public:
	Controller();
	~Controller();
	void update();
private:
	SDL_GameController *m_controller;
};
#endif // !CONTROLLER
