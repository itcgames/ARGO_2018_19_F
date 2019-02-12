#ifndef MOVING_STATE_H
#define MOVING_STATE_H

#include "States/PlayerState.h"

static class MovingState : public PlayerState
{
public:
	MovingState() {}
	virtual PlayerState* handleInput(Entity* entity, ControllerState& state);
	virtual void update(Entity* entity);
};
#endif // !MOVING_STATE_H
