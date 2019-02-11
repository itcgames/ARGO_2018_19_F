#ifndef IDLE_STATE_H
#define IDLE_STAT_H

#include "States/PlayerState.h"

class IdleState : public PlayerState
{
public:
	IdleState() {};
	inline virtual void handleInput(Entity& entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE)
	{
		AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
		ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

		if (animationComponent != nullptr)
		{
			Vector leftStick = Vector(SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controllerComponent->m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);

			// moving state
			if (leftStick.x > controllerComponent->DEAD_ZONE)
			{
				// change direction animation
				std::cout << "going right" << std::endl;
			}

			// jumping state
			if (buttons["a"])
			{
				std::cout << "jump" << std::endl;
			}

			// dead state
			if (buttons["start"])
			{
				std::cout << "pause" << std::endl;
			}

			// crouch state
			if (buttons["b"])
			{
				std::cout << "crouch" << std::endl;
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
#endif // !IDLE_STATE_H
