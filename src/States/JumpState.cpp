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
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

	if (animationComponent != nullptr)
	{
		Vector leftStick = controllerComponent->getCurrentState().leftStick;
		// change state
		if (leftStick.x > controllerComponent->DEAD_ZONE)
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
