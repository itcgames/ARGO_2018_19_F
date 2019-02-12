#include "States/JumpState.h"
#include "States/IdleState.h"

/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <param name="buttons"></param>
/// <param name="MAX_STICK_VALUE"></param>
/// <returns></returns>
PlayerState * JumpState::handleInput(Entity & entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

	if (animationComponent != nullptr)
	{
		Vector leftStick = Vector(SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);

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
