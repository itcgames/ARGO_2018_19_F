#ifndef DEATH_STATE_H
#define DEATH_STATE_H

#include "States/PlayerState.h"

class DeathState : public PlayerState
{
public:
	DeathState() {};
	virtual PlayerState* handleInput(Entity* entity, ControllerState& state);
	virtual void update(Entity* entity);
};
#endif // !DEATH_STATE_H
