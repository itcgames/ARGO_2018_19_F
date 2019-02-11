#ifndef JUMP_STATE_H
#define JUMP_STATE_H

#include "States/PlayerState.h"

class JumpState : public PlayerState
{
	JumpState() {};
	inline virtual void handleInput(Entity& entity, ControllerComponent* controller, const float MAX_STICK_VALUE)
	{
		AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");

		if (animationComponent != nullptr)
		{
			Vector leftStick = Vector(SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);

			// change state
			if (leftStick.x > controller->DEAD_ZONE)
			{
				// change direction animation
				std::cout << "going right" << std::endl;
			}
		}
	}

	inline virtual void update(Entity& entity)
	{
		// update
		AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");

		if (animationComponent != nullptr)
		{
			// change state
		}
	}
};
#endif // !JUMP_STATE_H
