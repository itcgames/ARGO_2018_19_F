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
PlayerState * MovingState::handleInput(Entity* entity, ControllerState& state)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");

	Vector leftStick = state.leftStick;

	if (animationComponent != nullptr)
	{
		if (state.A)
		{
			return new JumpState();
		}

		if (state.B)
		{
			return new CrouchState();
		}

		if (leftStick.x < controllerComponent->DEAD_ZONE && leftStick.x > -controllerComponent->DEAD_ZONE)
		{
			Vector frame = Vector(0, 0, 0);
			Vector lastFrame = Vector(1, 0, 0);
			animationComponent->setFirstFrame(frame);
			animationComponent->setLastFrame(lastFrame);
			return new IdleState();
		}
		else
		{
			if (leftStick.x < controllerComponent->DEAD_ZONE)
			{
				Vector firstFrame = Vector(3, 0, 0);
				Vector lastFrame = Vector(5,0,0);
				animationComponent->setFirstFrame(firstFrame);
				animationComponent->setLastFrame(lastFrame);
			}
			else
			{
				Vector firstFrame = Vector(3, 0, 0);
				Vector lastFrame = Vector(5, 0, 0);
				animationComponent->setFirstFrame(firstFrame);
				animationComponent->setLastFrame(lastFrame);
			}
		}
	}

	return nullptr;
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void MovingState::update(Entity* entity)
{
	std::cout << "moving" << std::endl;
}
