#ifndef MOVING_STATE_H
#define MOVING_STATE_H

#include "States/PlayerState.h"

static class MovingState : public PlayerState
{
public:
	MovingState() {}
	virtual PlayerState* handleInput(Entity& entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE);
	virtual void update(Entity& entity);
};
#endif // !MOVING_STATE_H
