#ifndef VICTORY_STATE_H
#define VICTORY_STATE_H

//  Project.
#include "States/PlayerState.h"

class VictoryState : public PlayerState
{
public:
	VictoryState() {};
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);
};
#endif // !VICTORY_STATE_H
