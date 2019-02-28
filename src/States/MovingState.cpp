#include "States/MovingState.h"
#include "States/IdleState.h"
#include "States/JumpState.h"
#include "States/CrouchState.h"
#include "States/VictoryState.h"
#include "States/DeathState.h"

MovingState::MovingState()
{
	m_stateId = "Moving";
	m_jumpSound = Mix_LoadWAV("./resources/Sounds/jump.wav");
}

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
	AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");
	PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
	PlayerStateComponent* playerStateComponent = (PlayerStateComponent*)entity->getComponent("PLAYER_STATE");

	if (state.leftStick.x > controllerComponent->DEAD_ZONE)
	{
		animationComponent->m_flip = SDL_FLIP_NONE;
		if (physicsComponent->getVelocity().x <= physicsComponent->getMaxVelocity().x)
		{
			physicsComponent->addAcceleration(0.075, 0);
		}
	}
	else if (state.leftStick.x < -controllerComponent->DEAD_ZONE)
	{
		animationComponent->m_flip = SDL_FLIP_HORIZONTAL;
		if (physicsComponent->getVelocity().x >= -physicsComponent->getMaxVelocity().x)
		{
			physicsComponent->addAcceleration(-0.075, 0);
		}
	}

	// switch to jump
	if (state.A)
	{
		physicsComponent->setJumping(true);
		Mix_PlayChannel(3, m_jumpSound, 0);
		physicsComponent->addAcceleration(0, -1.5);
		return new JumpState();
	}

	// switch to crouch
	if (state.B)
	{
		return new CrouchState();
	}

	// switch to idle
	if (state.leftStick.x < controllerComponent->DEAD_ZONE && state.leftStick.x > -controllerComponent->DEAD_ZONE)
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
void MovingState::update(double dt, Entity* entity)
{
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
		Vector firstFrame = Vector(0, 0);
		Vector lastFrame = Vector(3, 0);
		animationComponent->setFirstFrame(firstFrame);
		animationComponent->setCurrentFrame(firstFrame);
		animationComponent->setLastFrame(lastFrame);
	}
}
