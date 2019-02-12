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
		if (leftStick.x > controllerComponent->DEAD_ZONE || leftStick.x < -controllerComponent->DEAD_ZONE)
		{
			if (leftStick.x > controllerComponent->DEAD_ZONE)
			{
				animationComponent->m_flip = SDL_FLIP_NONE;
			}
			else
			{
				animationComponent->m_flip = SDL_FLIP_HORIZONTAL;
			}
		}

		// change state
		if (!physicsComponent->getJumping())
		{
			Vector firstFrame = Vector(0, 0, 0);
			Vector lastFrame = Vector(1, 0, 0);
			animationComponent->setFirstFrame(firstFrame);
			animationComponent->setCurrentFrame(firstFrame);
			animationComponent->setLastFrame(lastFrame);
			return new IdleState();
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
