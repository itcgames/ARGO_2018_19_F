#pragma once
#ifndef CONTROLLER
#define CONTROLLER
#define MAX_CONTROLLERS 4

#include<string>
#include<SDL_gamecontroller.h>
#include "SDL2_Helper/SDL2Helper.h"
#include<iostream>
#include"ECS/Components/Component.h"

class Controller : public Component
{

public:
	Controller();

	SDL_GameController *m_controller;
};
#endif // !CONTROLLER
