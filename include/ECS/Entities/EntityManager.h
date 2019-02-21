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
#include "ECS/Components/UIComponent.h"
#include "ECS/Components/TextComponent.h"
//	Systems.
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/NetworkSystem.h"
#include "ECS/Systems/BoxPhysicsSystem.h"
#include "ECS/Systems/CursorControlSystem.h"
#include "ECS/Systems/UIGraphicsSystem.h"
#include "ECS/Systems/AISystem.h"

class EntityManager
{
public:
	EntityManager();
	EntityManager(std::pair<std::string, Client*> client);
	~EntityManager();

	//	Entity Constructors.
	void createPlayer(int playerNum, Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider, bool controllable);
	void createAI(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createSpring(Vector position, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createBackground(SDL_Texture* texture, SDL_Rect srcRect);
	void createSelectionBox(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect);
	void createCursor(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createStart(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createGoal(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createLabel(Vector position, std::string text, SDL_Color colour, int width, int height);
	void createButton(int order, bool selected, Vector position, SDL_Texture* texture, SDL_Rect src, std::string text, SDL_Color colour, int width, int height);

	GraphicsSystem * getGraphicsSystem();
	PhysicsSystem * getPhysicsSystem();
	CollisionSystem * getCollisionSystem();
	CharacterControlSystem * getCharacterControlSystem();
	NetworkSystem * getNetworkSystem();
	CursorControlSystem * getCursorControlSystem();
	BoxPhysicsSystem * getBoxPhysicsSystem();
	UIGraphicsSystem * getUIGraphicsSystem();
	AISystem * getAISystem();

private:
	void addToSystems(Entity* entity);

	//	Systems	
	std::map<std::string, System*> m_systems;

	//	Entity master list.
	std::vector<Entity*> m_entities;

	std::pair<std::string, Client*> m_client;
};
#endif // !ENTITY_MANAGER_H
