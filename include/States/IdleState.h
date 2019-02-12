#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "States/PlayerState.h"

class IdleState : public PlayerState
{
public:
	IdleState() {};
	virtual PlayerState* handleInput(Entity& entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE);
	virtual void update(Entity& entity);
};
#endif // !IDLE_STATE_H
