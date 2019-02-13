#ifndef MOVING_STATE_H
#define MOVING_STATE_H

//  Project.
#include "States/PlayerState.h"

static class MovingState : public PlayerState
{
public:
	MovingState() {}
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);
};
#endif // !MOVING_STATE_H
