#include "States/CrouchState.h"
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
PlayerState * CrouchState::handleState(Entity* entity, ControllerState& state)
{
	ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");
	PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
	GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("GRAPHICS");
	CollisionComponent* collisionComponent = (CollisionComponent*)entity->getComponent("COLLISION");
	PlayerStateComponent* playerStateComponent = (PlayerStateComponent*)entity->getComponent("PLAYER_STATE");

	SDL_Rect destRect = graphicsComponent->getDestRect();
	graphicsComponent->setDestRect({ destRect.x, destRect.y, destRect.w , CROUCH_HEIGHT });
	SDL_Rect rect = { collisionComponent->getCollider().x, collisionComponent->getCollider().y, collisionComponent->getCollider().w, CROUCH_HEIGHT };
	collisionComponent->setCollider(rect);
	Vector v = { positionComponent->getPos().x, positionComponent->getPos().y + STAND_HEIGHT - CROUCH_HEIGHT };
	positionComponent->setPos(v);

	// change state
	if (!state.B)
	{
		SDL_Rect destRect = graphicsComponent->getDestRect();
		graphicsComponent->setDestRect({ destRect.x, destRect.y, destRect.w , STAND_HEIGHT });
		SDL_Rect rect = { collisionComponent->getCollider().x, collisionComponent->getCollider().y, collisionComponent->getCollider().w, STAND_HEIGHT };
		collisionComponent->setCollider(rect);
		// change direction animation
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
