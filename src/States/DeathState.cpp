#include "States/DeathState.h"
#include "States/IdleState.h"

/// <summary>
/// process any input updates then if any parameters are met 
/// instansiate a new state and return it from the method transitioning the
/// player to the new state - if no new state required return nullptr
/// </summary>
/// <param name="entity">pointer to entity for component selection</param>
/// <param name="state">controller state for animation</param>
/// <returns>default - nullptr, pointer to a PlayerState child</returns>
PlayerState * DeathState::handleState(Entity * entity, ControllerState & state)
{
	PlayerStateComponent* playerStateComponent = (PlayerStateComponent*)entity->getComponent("PLAYER_STATE");

	if (playerStateComponent != nullptr)
	{
		if (playerStateComponent->isAlive())
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
void DeathState::update(double dt, Entity * entity)
{
	m_timeToDie += dt;
	if (m_timeToDie > m_deathAnimation && m_timeToDie <= m_deathAnimation + dt)
	{
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
}



/// <summary>
/// set up the animation frames for the state 
/// </summary>
/// <param name="entity">pointer to the entity object</param>
void DeathState::enter(Entity * entity)
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
