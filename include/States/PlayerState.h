#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

//  Project.
#include "ECS/Entities/Entity.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/PlayerStateComponent.h"

class PlayerState
{
public:
	~PlayerState() {};
	virtual PlayerState* handleState(Entity* entity, ControllerState& state) = 0;
	virtual void update(double dt, Entity *entity) = 0;
	virtual void enter(Entity* entity) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string getStateId() { return m_stateId; }

protected:
	std::string m_stateId;
};
#endif // !PLAYER_STATE_H
