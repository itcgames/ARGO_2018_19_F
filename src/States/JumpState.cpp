#include "States/JumpState.h"
#include "States/IdleState.h"

/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <param name="buttons"></param>
/// <param name="MAX_STICK_VALUE"></param>
/// <returns></returns>
PlayerState * JumpState::handleInput(Entity & entity, ControllerState& state)
{
	PhysicsComponent* physicsComponent = (PhysicsComponent*)entity.getComponent("PHYSICS");

	if (physicsComponent != nullptr)
	{
		// change state
		if (!physicsComponent->getJumping())
		{
			// change direction animation
			return new IdleState();
		}
	}

	return nullptr;
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void JumpState::update(Entity & entity)
{
	// update
	std::cout << "jumping" << std::endl;
}
