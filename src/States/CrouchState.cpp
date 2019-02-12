#include "States/CrouchState.h"
#include "States/IdleState.h"

/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <param name="buttons"></param>
/// <param name="MAX_STICK_VALUE"></param>
/// <returns></returns>
PlayerState * CrouchState::handleInput(Entity & entity, ControllerState& state)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

	if (animationComponent != nullptr)
	{
		// change state
		if (!controllerComponent->getCurrentState().B)
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
void CrouchState::update(Entity & entity)
{
	std::cout << "crouching" << std::endl;
}
