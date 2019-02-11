#ifndef ENTITY_CREATOR_H
#define ENTITY_CREATOR_H

//	Entity
#include "ECS/Entities/Entity.h"
//	Systems
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/ControlSystem.h"
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"

namespace EntityCreator
{
	Entity* createPlayer(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	Entity* createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	Entity* createPlatform(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	Entity* createBackground(SDL_Texture* texture, SDL_Rect srcRect);

	Entity* createStart(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	Entity* createGoal(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
};
#endif // !ENTITY_CREATOR_H
