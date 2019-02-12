#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "States/PlayerState.h"

class IdleState : public PlayerState
{
public:
	IdleState() {};
	virtual PlayerState* handleInput(Entity& entity, ControllerState& state);
	virtual void update(Entity& entity);
};
#endif // !IDLE_STATE_H
