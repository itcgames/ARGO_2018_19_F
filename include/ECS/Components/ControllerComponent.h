#ifndef CONTROLLER_COMPONENT_H
#define CONTROLLER_COMPONENT_H
//  Standard.
#include<string>
#include<SDL_gamecontroller.h>
#include<iostream>
//  Project.
#include "SDL2_Helper/SDL2Helper.h"
#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

struct ControllerState
{
	//	Dpad.
	bool dpadUp;
	bool dpadDown;
	bool dpadLeft;
	bool dpadRight;
	//  Centre buttons.
	bool start;
	bool back;
	//  Shoulder buttons.
	bool leftShoulder;
	bool rightShoulder;
	//  Face buttons.
	bool A;
	bool B;
	bool X;
	bool Y;
	//  Sticks.
	Vector leftStick;
	Vector rightStick;
	//	Triggers.
	float leftTrigger;
	float rightTrigger;
};

class ControllerComponent : public Component
{
public:
	ControllerComponent();		

	ControllerState& getCurrentState();
	ControllerState& getPreviousState();

    const float DEAD_ZONE = 0.3f;	
    static int m_controllerIndex;		

private:
	ControllerState m_currentState;
	ControllerState m_previousState;

	SDL_GameController* m_controller;

	const float MAX_STICK_VALUE = SDL_MAX_SINT16;
	const float MAX_TRIGGER_VALUE = 32767.0f;	// Int max
};
#endif // !CONTROLLER_COMPONENT_H
