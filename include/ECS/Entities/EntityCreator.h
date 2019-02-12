#ifndef ENTITY_CREATOR_H
#define ENTITY_CREATOR_H

//	Entity
#include "ECS/Entities/Entity.h"
//	Systems
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/BoxPhysicsSystem.h"

namespace EntityCreator
{
	Entity* createPlayer(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	Entity* createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	Entity* createPlatform(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	Entity* createBackground(SDL_Texture* texture, SDL_Rect srcRect);
	Entity* createSelectionBox(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
	Entity* createCursor(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);

	Entity* createStart(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	Entity* createGoal(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
};
#endif // !ENTITY_CREATOR_H
