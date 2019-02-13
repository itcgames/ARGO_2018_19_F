#ifndef CROUCH_STATE_H
#define CROUCH_STATE_H

#include "States/PlayerState.h"

class CrouchState : public PlayerState
{
public:
	CrouchState() {};
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);
};
#endif // !CROUCH_STATE_H
