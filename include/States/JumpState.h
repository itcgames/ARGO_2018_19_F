#ifndef JUMP_STATE_H
#define JUMP_STATE_H

//  Project.
#include "States/PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState() { m_stateId = "Jump"; };
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);
};
#endif // !JUMP_STATE_H
