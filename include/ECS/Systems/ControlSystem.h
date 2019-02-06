#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/Controller.h"
#include "ECS/Components/PositionComponent.h"

class ControlSytem : public System
{
public:
	void update(double dt, SDL_Event e);
	virtual void update(double dt) override {};

private:
	std::string m_btnName;
	SDL_GameController *m_controller;
	SDL_GameController *m_controllerHandles[MAX_CONTROLLERS];
};

#endif // !CONTROLSYSTEM_H

