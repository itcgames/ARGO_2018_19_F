#include "States/MovingState.h"
#include "States/IdleState.h"
#include "States/JumpState.h"
#include "States/CrouchState.h"

/// <summary>
/// process any input updates then if any parameters are met 
/// instansiate a new state and return it from the method transitioning the
/// player to the new state - if no new state required return nullptr
/// </summary>
/// <param name="entity">pointer to entity for component selection</param>
/// <param name="state">controller state for animation</param>
/// <returns>default - nullptr, pointer to a PlayerState child</returns>
PlayerState * MovingState::handleState(Entity* entity, ControllerState& state)
{
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");
	Vector leftStick = state.leftStick;

	// switch to jump
	if (state.A)
	{
		return new JumpState();
	}

	// switch to crouch
	if (state.B)
	{
		return new CrouchState();
	}

	// switch to idle
	if (leftStick.x < controllerComponent->DEAD_ZONE && leftStick.x > -controllerComponent->DEAD_ZONE)
	{
		return new IdleState();
	}

	return nullptr;
}



/// <summary>
/// update the state - change the current animation frames if time constraints met
/// </summary>
/// <param name="dt">game clock</param>
/// <param name="entity">pointer to the entity object</param>
void MovingState::update(double dt, Entity* entity)
{
	std::cout << "moving" << std::endl;
}



/// <summary>
/// set up the animation frames for the state 
/// </summary>
/// <param name="entity">pointer to the entity object</param>
void MovingState::enter(Entity* entity)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	if (animationComponent != nullptr)
	{
		Vector firstFrame = Vector(3, 0, 0);
		Vector lastFrame = Vector(5, 0, 0);
		animationComponent->setFirstFrame(firstFrame);
		animationComponent->setCurrentFrame(firstFrame);
		animationComponent->setLastFrame(lastFrame);
	}
}
