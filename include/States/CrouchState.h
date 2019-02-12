#ifndef CROUCH_STATE_H
#define CROUCH_STATE_H

#include "States/PlayerState.h"

class CrouchState : public PlayerState
{
public:
	CrouchState() {};
	virtual PlayerState* handleInput(Entity& entity, ControllerState& state);
	virtual void update(Entity& entity);
};
#endif // !CROUCH_STATE_H
