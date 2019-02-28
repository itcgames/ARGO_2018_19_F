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
PlayerState* IdleState::handleState(Entity* entity, ControllerState& state)
{
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");
	PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
	PlayerStateComponent* playerStateComponent = (PlayerStateComponent*)entity->getComponent("PLAYER_STATE");

	Vector leftStick = state.leftStick;
	// moving state
	if (leftStick.x > controllerComponent->DEAD_ZONE || leftStick.x < -controllerComponent->DEAD_ZONE)
	{
		return new MovingState();
	}
	else
	{
		Vector zero = Vector::Zero();
		physicsComponent->setVelocity(zero);
	}

	// jumping state
	if (state.A)
	{
		physicsComponent->setJumping(true);
		Mix_PlayChannel(3, m_jumpSound, 0);
		physicsComponent->addAcceleration(0, -1.5);
		return new JumpState();
	}

	// dead // pause state
	if (state.start)
	{
		return nullptr;
	}

	// crouch state
	if (state.B)
	{
		return new CrouchState();
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
	// set up sprite frames
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	if (animationComponent != nullptr)
	{
		Vector firstFrame = Vector(0, 0);
		Vector lastFrame = Vector(0, 0);
		animationComponent->setFirstFrame(firstFrame);
		animationComponent->setCurrentFrame(firstFrame);
		animationComponent->setLastFrame(lastFrame);
	}
}
