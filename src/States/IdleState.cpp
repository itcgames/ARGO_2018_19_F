#include "States/IdleState.h"
#include "States/JumpState.h"
#include "States/CrouchState.h"
#include "States/MovingState.h"

/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <param name="buttons"></param>
/// <param name="MAX_STICK_VALUE"></param>
/// <returns></returns>
PlayerState* IdleState::handleInput(Entity & entity, ControllerState& state)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

	if (animationComponent != nullptr)
	{
		Vector leftStick = controllerComponent->getCurrentState().leftStick;
		// moving state
		if (leftStick.x > controllerComponent->DEAD_ZONE || leftStick.x < -controllerComponent->DEAD_ZONE)
		{
			// change direction animation
			return new MovingState();
		}

		// jumping state
		if (controllerComponent->getCurrentState().A)
		{
			return new JumpState();
		}

		// dead state
		if (controllerComponent->getCurrentState().start)
		{
			std::cout << "pause" << std::endl;
			return nullptr;
		}

		// crouch state
		if (controllerComponent->getCurrentState().B)
		{
			return new CrouchState();
		}
	}

	return nullptr;
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void IdleState::update(Entity & entity)
{
	std::cout << "idle" << std::endl;
}
