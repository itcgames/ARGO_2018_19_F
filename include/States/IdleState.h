#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "States/PlayerState.h"
#include "States/JumpState.h"
#include "States/CrouchState.h"
#include "States/MovingState.h"
#include "States/DeathState.h"

class IdleState : public PlayerState
{
public:
	IdleState() {};
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);
};
#endif // !IDLE_STATE_H
