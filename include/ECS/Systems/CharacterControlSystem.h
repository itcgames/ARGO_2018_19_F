#ifndef CHARACTER_CONTROL_SYSTEM_H
#define CHARACTER_CONTROL_SYSTEM_H
//  Standard.
#include <map>
//  Project.
#include "ECS/Systems/System.h"
#include "Vector/Vector.h"
#include "States/IdleState.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"

class CharacterControlSystem : public System
{
public:
	void update(double dt, SDL_Event e);	
	virtual void update(double dt) override {};

	PlayerState* m_state = new IdleState();
};
#endif // !CHARACTER_CONTROL_SYSTEM_H