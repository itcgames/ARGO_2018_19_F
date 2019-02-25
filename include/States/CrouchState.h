#ifndef CROUCH_STATE_H
#define CROUCH_STATE_H

//  Project.
#include "States/PlayerState.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/CollisionComponent.h"

class CrouchState : public PlayerState
{
public:
	CrouchState() { m_stateId = "Crouching"; };
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);

private:
	const int CROUCH_HEIGHT = 80;
	const int STAND_HEIGHT = 96;
};
#endif // !CROUCH_STATE_H
