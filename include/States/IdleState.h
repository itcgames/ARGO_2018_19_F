#ifndef IDLE_STATE_H
#define IDLE_STATE_H

//  Project.
#include "States/PlayerState.h"
#include "States/JumpState.h"
#include "States/CrouchState.h"
#include "States/MovingState.h"
#include "States/DeathState.h"
#include <SDL_mixer.h>

class IdleState : public PlayerState
{
public:
	IdleState() { m_stateId = "Idle"; };
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);

private:
	Mix_Chunk * m_jumpSound;
};
#endif // !IDLE_STATE_H
