#ifndef MOVING_STATE_H
#define MOVING_STATE_H

//  Project.
#include "States/PlayerState.h"
#include <SDL_mixer.h>

static class MovingState : public PlayerState
{
public:
	MovingState();
	virtual PlayerState* handleState(Entity* entity, ControllerState& state);
	virtual void update(double dt, Entity* entity);
	virtual void enter(Entity* entity);

private:
	Mix_Chunk * m_jumpSound;
};
#endif // !MOVING_STATE_H
