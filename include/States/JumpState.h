#ifndef JUMP_STATE_H
#define JUMP_STATE_H

#include "States/PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState() {};
	virtual PlayerState* handleInput(Entity& entity, ControllerState& state);
	virtual void update(Entity& entity);
};
#endif // !JUMP_STATE_H
