#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "ECS/Entities/Entity.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/AnimationComponent.h"

class PlayerState
{
public:
	~PlayerState() {};
	virtual PlayerState* handleInput(Entity& entity, ControllerState& state) = 0;
	virtual void update(Entity &entity) = 0;
};
#endif // !PLAYER_STATE_H
