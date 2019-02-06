#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H
#define MAX_CONTROLLERS 4

#include<string>
#include<SDL_gamecontroller.h>
#include "SDL2_Helper/SDL2Helper.h"
#include<iostream>
#include"ECS/Components/Component.h"

class ControllerComponent : public Component
{
public:
	ControllerComponent();

	SDL_GameController *m_controller;
};
#endif // !CONTROLLER_COMPONENT_H