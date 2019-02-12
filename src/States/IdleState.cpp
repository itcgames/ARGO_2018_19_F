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
PlayerState* IdleState::handleInput(Entity & entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

	if (animationComponent != nullptr)
	{
		Vector leftStick = Vector(SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);

		// moving state
		if (leftStick.x > controllerComponent->DEAD_ZONE || leftStick.x < -controllerComponent->DEAD_ZONE)
		{
			// change direction animation
			return new MovingState();
		}

		// jumping state
		if (buttons["a"])
		{
			return new JumpState();
		}

		// dead state
		if (buttons["start"])
		{
			std::cout << "pause" << std::endl;
			return nullptr;
		}

		// crouch state
		if (buttons["b"])
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
