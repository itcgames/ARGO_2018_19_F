#include "States/CrouchState.h"
#include "States/IdleState.h"

/// <summary>
/// process any input updates then if any parameters are met 
/// instansiate a new state and return it from the method transitioning the
/// player to the new state - if no new state required return nullptr
/// </summary>
/// <param name="entity">pointer to entity for component selection</param>
/// <param name="state">controller state for animation</param>
/// <returns>default - nullptr, pointer to a PlayerState child</returns>
PlayerState * CrouchState::handleState(Entity* entity, ControllerState& state)
{
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");

	// change state
	if (!state.B)
	{
		// change direction animation
		return new IdleState();
	}

	return nullptr;
}



/// <summary>
/// update the state - change the current animation frames if time constraints met
/// </summary>
/// <param name="dt">game clock</param>
/// <param name="entity">pointer to the entity object</param>
void CrouchState::update(double dt, Entity* entity)
{
}



/// <summary>
/// set up the animation frames for the state 
/// </summary>
/// <param name="entity">pointer to the entity object</param>
void CrouchState::enter(Entity * entity)
{
	// set up sprite frames
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	if (animationComponent != nullptr)
	{
	}
}
