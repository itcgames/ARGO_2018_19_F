#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "ECS/Entities/Entity.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/AnimationComponent.h"

class PlayerState
{
public:
	~PlayerState() {};
	virtual PlayerState* handleInput(Entity& entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE) {};
	virtual void update(Entity &entity) {};
};
#endif // !PLAYER_STATE_H
