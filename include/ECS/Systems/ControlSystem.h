#ifndef CONTROLSYSTEM_H
#define CONTROLSYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/Controller.h"
#include "ECS/Components/PositionComponent.h"

class ControlSytem : public System
{
public:
	 virtual void update(double dt);

private:
	//Vector m_gravity = Vector(0, .0098, 0);
	std::string m_btnName;
	Controller *m_controller;
};

#endif // !CONTROLSYSTEM_H

