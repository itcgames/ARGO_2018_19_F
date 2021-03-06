#ifndef DEATH_STATE_H
#define DEATH_STATE_H

//  Project.
#include "States/PlayerState.h"

class DeathState : public PlayerState
{
public:
	DeathState() { m_stateId = "Death"; };
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);

	double m_timeToDie = 0.0;
	double m_deathAnimation = 120.0;
};
#endif // !DEATH_STATE_H
