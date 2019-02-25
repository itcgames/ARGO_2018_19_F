#include "States/JumpState.h"
#include "States/IdleState.h"
#include "States/VictoryState.h"
#include "States/DeathState.h"

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
	PlayerStateComponent* playerStateComponent = (PlayerStateComponent*)entity->getComponent("PLAYER_STATE");

	if (state.leftStick.x > controllerComponent->DEAD_ZONE)
	{
		animationComponent->m_flip = SDL_FLIP_NONE;
		if (physicsComponent->getVelocity().x <= physicsComponent->getMaxJumpVelocity().x)
		{
			physicsComponent->addAcceleration(0.075, 0);
		}
	}
	else if (state.leftStick.x < -controllerComponent->DEAD_ZONE)
	{
		animationComponent->m_flip = SDL_FLIP_HORIZONTAL;
		if (physicsComponent->getVelocity().x >= -physicsComponent->getMaxJumpVelocity().x)
		{
			physicsComponent->addAcceleration(-0.075, 0);
		}
	}

	// change state
	if (!physicsComponent->getJumping())
	{
		return new IdleState();
	}

	if (playerStateComponent->hasWon())
	{
		return new VictoryState();
	}

	if (!playerStateComponent->isAlive())
	{
		return new DeathState();
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
