#ifndef CHARACTER_CONTROL_SYSTEM_H
#define CHARACTER_CONTROL_SYSTEM_H
//  Standard.
#include <map>
//  Project.
#include "ECS/Systems/System.h"
#include "Vector/Vector.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PhysicsComponent.h"

class CharacterControlSystem : public System
{
public:
	void update(double dt, SDL_Event e);
	virtual void update(double dt) override {};    
};
#endif // !CHARACTER_CONTROL_SYSTEM_H