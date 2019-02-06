#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PositionComponent.h"

class ControlSystem : public System
{
public:
	void update(double dt, SDL_Event e);
	virtual void update(double dt) override {};
};
#endif // !CONTROL_SYSTEM_H