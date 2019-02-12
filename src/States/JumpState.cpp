#include "States/JumpState.h"
#include "States/IdleState.h"

/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
/// <param name="buttons"></param>
/// <param name="MAX_STICK_VALUE"></param>
/// <returns></returns>
PlayerState * JumpState::handleInput(Entity* entity, ControllerState& state)
{
	PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");

	Vector leftStick = state.leftStick;

	if (physicsComponent != nullptr)
	{
		// change state
		if (!physicsComponent->getJumping())
		{
			Vector frame = Vector(0, 0, 0);
			animationComponent->setFirstFrame(frame);
			// change direction animation
			return new IdleState();
		}

		if (leftStick.x > controllerComponent->DEAD_ZONE || leftStick.x < -controllerComponent->DEAD_ZONE)
		{
			if (leftStick.x > controllerComponent->DEAD_ZONE)
			{
				Vector frame = Vector(1,0);
				animationComponent->setFirstFrame(frame);
			}
			else
			{
				Vector frame = Vector(2, 0, 0);
				animationComponent->setFirstFrame(frame);
			}
		}
		else
		{
			Vector frame = Vector(3, 0, 0);
			animationComponent->setFirstFrame(frame);
		}
	}

	return nullptr;
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void JumpState::update(Entity* entity)
{
	// update
	std::cout << "jumping" << std::endl;
}
