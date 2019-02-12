#ifndef JUMP_STATE_H
#define JUMP_STATE_H

#include "States/PlayerState.h"

class JumpState : public PlayerState
{
public:
	JumpState() {};
	virtual PlayerState* handleInput(Entity& entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE);
	virtual void update(Entity& entity);
};
#endif // !JUMP_STATE_H
