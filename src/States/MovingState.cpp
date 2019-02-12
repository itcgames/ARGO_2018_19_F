#include "States/MovingState.h"
#include "States/IdleState.h"
#include "States/JumpState.h"
#include "States/CrouchState.h"

/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <param name="buttons"></param>
/// <param name="MAX_STICK_VALUE"></param>
/// <returns></returns>
PlayerState * MovingState::handleInput(Entity & entity, ControllerState& state)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

	Vector leftStick = controllerComponent->getCurrentState().leftStick;

	if (animationComponent != nullptr)
	{
		if (controllerComponent->getCurrentState().A)
		{
			return new JumpState();
		}

		if (controllerComponent->getCurrentState().B)
		{
			return new CrouchState();
		}

		if (leftStick.x < controllerComponent->DEAD_ZONE && leftStick.x > -controllerComponent->DEAD_ZONE)
		{
			return new IdleState();
		}
	}

	return nullptr;
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void MovingState::update(Entity & entity)
{
	std::cout << "moving" << std::endl;
}
