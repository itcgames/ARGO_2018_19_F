#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

//	Entity
#include "ECS/Entities/Entity.h"
//	Components
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/NetworkComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/PositionComponent.h"
//	Systems.
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/NetworkSystem.h"

class EntityManager
{
public:
	EntityManager(Client* client);
	~EntityManager();
	//	Entity Constructors.
	void createPlayer(int playerNum, Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider, bool controllable);
	void createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createBackground(SDL_Texture* texture, SDL_Rect srcRect);
	void createStart(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createGoal(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);

	GraphicsSystem * getGraphicsSystem();
	PhysicsSystem * getPhysicsSystem();
	CollisionSystem * getCollisionSystem();
	CharacterControlSystem * getCharacterControlSystem();
	NetworkSystem * getNetworkSystem();

private:
	void addToSystems(Entity* entity);

	//	Systems	
	GraphicsSystem m_graphicsSystem;
	PhysicsSystem m_physicsSystem;
	CollisionSystem m_collisionSystem;
	CharacterControlSystem m_characterControlSystem;
	NetworkSystem m_networkSystem;
	//	Entity master list.
	std::vector<Entity*> m_entities;
};
#endif // !ENTITY_MANAGER_H
