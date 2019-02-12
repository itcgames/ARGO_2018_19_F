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
PlayerState * MovingState::handleInput(Entity & entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");
	Vector leftStick = Vector(SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);

	if (animationComponent != nullptr)
	{
		if (buttons["a"])
		{
			return new JumpState();
		}

		if (buttons["b"])
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
