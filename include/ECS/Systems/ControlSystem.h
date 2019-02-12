#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H
//  Standard.
#include <map>
//  Project.
#include "ECS/Systems/System.h"
#include "Vector/Vector.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS\Components\CollisionComponent.h"

class ControlSystem : public System
{
public:
	void update(double dt, SDL_Event e);
	
	virtual void update(double dt) override {};
private:
    const float MAX_STICK_VALUE = SDL_MAX_SINT16;
};
#endif // !CONTROL_SYSTEM_H