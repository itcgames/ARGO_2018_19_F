#include "States/IdleState.h"

/// <summary>
/// process any input updates then if any parameters are met 
/// instansiate a new state and return it from the method transitioning the
/// player to the new state - if no new state required return nullptr
/// </summary>
/// <param name="entity">pointer to entity for component selection</param>
/// <param name="state">controller state for animation</param>
/// <returns>default - nullptr, pointer to a PlayerState child</returns>
PlayerState* IdleState::handleState(Entity* entity, ControllerState& state)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");
	if (animationComponent != nullptr)
	{
		Vector leftStick = state.leftStick	;
		// moving state
		if (leftStick.x > controllerComponent->DEAD_ZONE || leftStick.x < -controllerComponent->DEAD_ZONE)
		{
			// change direction animation
			if (leftStick.x < controllerComponent->DEAD_ZONE)
			{
				animationComponent->m_flip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				animationComponent->m_flip = SDL_FLIP_NONE;
			}

			return new MovingState();
		}

		// jumping state
		if (state.A)
		{
			return new JumpState();
		}

		// dead // pause state
		if (state.start)
		{
			std::cout << "pause" << std::endl;
			return nullptr;
		}

		// crouch state
		if (state.B)
		{
			return new CrouchState();
		}
	}

	return nullptr;
}



/// <summary>
/// update the state - change the current animation frames if time constraints met
/// </summary>
/// <param name="dt">game clock</param>
/// <param name="entity">pointer to the entity object</param>
void IdleState::update(double dt, Entity* entity)
{
	// waiting animation switch
}




/// <summary>
/// set up the animation frames for the state 
/// </summary>
/// <param name="entity">pointer to the entity object</param>
void IdleState::enter(Entity* entity)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	if (animationComponent != nullptr)
	{
		Vector firstFrame = Vector(0, 0, 0);
		Vector lastFrame = Vector(1, 0, 0);
		animationComponent->setFirstFrame(firstFrame);
		animationComponent->setCurrentFrame(firstFrame);
		animationComponent->setLastFrame(lastFrame);
	}
}
