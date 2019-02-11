#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H
//  Standard.
#include<string>
#include<SDL_gamecontroller.h>
#include<iostream>
//  Project.
#include "SDL2_Helper/SDL2Helper.h"
#include"ECS/Components/Component.h"

class ControllerComponent : public Component
{
public:
	ControllerComponent();
	SDL_GameController* m_controller;
    const float DEAD_ZONE = 0.3f;
    static int m_controllerIndex;
	bool m_paused;
};
#endif // !CONTROLLER_COMPONENT_H
