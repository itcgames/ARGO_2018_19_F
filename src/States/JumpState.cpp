#include "States/JumpState.h"
#include "States/IdleState.h"

/// <summary>
/// process any input updates then if any parameters are met 
/// instansiate a new state and return it from the method transitioning the
/// player to the new state - if no new state required return nullptr
/// </summary>
/// <param name="entity">pointer to entity for component selection</param>
/// <param name="state">controller state for animation</param>
/// <returns>default - nullptr, pointer to a PlayerState child</returns>
PlayerState * JumpState::handleState(Entity* entity, ControllerState& state)
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
			return new IdleState();
		}
	}

	return nullptr;
}



/// <summary>
/// update the state - change the current animation frames if time constraints met
/// </summary>
/// <param name="dt">game clock</param>
/// <param name="entity">pointer to the entity object</param>
void JumpState::update(double dt, Entity* entity)
{
	// update
}



/// <summary>
/// set up the animation frames for the state 
/// </summary>
/// <param name="entity">pointer to the entity object</param>
void JumpState::enter(Entity * entity)
{
	// set up sprite frames
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	if (animationComponent != nullptr)
	{
		Vector firstFrame = Vector(5, 1, 0);
		Vector lastFrame = Vector(5, 1, 0);
		animationComponent->setFirstFrame(firstFrame);
		animationComponent->setCurrentFrame(firstFrame);
		animationComponent->setLastFrame(lastFrame);
	}
}
