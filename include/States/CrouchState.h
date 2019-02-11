#ifndef CROUCH_STATE_H
#define CROUCH_STATE_H

#include "States/PlayerState.h"
#include "States/IdleState.h"

class CrouchState : public PlayerState
{
public:
	CrouchState() {};
	inline virtual PlayerState* handleInput(Entity& entity, std::map<std::string, bool>& buttons, const float MAX_STICK_VALUE)
	{
		AnimationComponent* animationComponent = (AnimationComponent*)entity.getComponent("ANIMATION");
		ControllerComponent* controllerComponent = (ControllerComponent*)entity.getComponent("CONTROLLER");

		if (animationComponent != nullptr)
		{
			// change state
			if (!buttons["b"])
			{
				// change direction animation
				std::cout << "going right" << std::endl;
				return new IdleState();
			}
		}

		return NULL;
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

#endif // !CROUCH_STATE_H
