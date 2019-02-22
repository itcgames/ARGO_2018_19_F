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
#include "ECS/Components/ButtonComponent.h"
#include "ECS/Components/TextComponent.h"
#include "ECS/Components/FuncButtonComponent.h"
//	Systems.
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/NetworkSystem.h"
#include "ECS/Systems/BoxPhysicsSystem.h"
#include "ECS/Systems/CursorControlSystem.h"
#include "ECS/Systems/UIGraphicsSystem.h"
#include "ECS/Systems/UIControlSystem.h"

class EntityManager
{
public:
	EntityManager(ScreenManager* screenManager, SDL_Renderer* renderer);
	~EntityManager();

	void update(double dt);
	void render();

	//	Entity Constructors.
	void createPlayer(int playerNum, Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider, bool controllable, bool online);
	void createKillBox(Vector startPosition, SDL_Rect collider);
	void createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createSpring(Vector position, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createBackground(SDL_Texture* texture, SDL_Rect srcRect);
	void createSelectionBox(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect);
	void createCursor(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);
	void createStart(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createGoal(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createLabel(Vector position, std::string text, SDL_Color colour, int width, int height);
	void createButton(int index, bool selected, std::string goTo, Vector position, std::string text, SDL_Color colour, int width, int height);
	void createImage(Vector position, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect);
	void createFunctionButton(Vector position, int index, bool selected, std::function<void()>  func, SDL_Texture* texture, int srcWidth, int srcHeight, int destWidth, int destHeight);

	GraphicsSystem * getGraphicsSystem();
	PhysicsSystem * getPhysicsSystem();
	CollisionSystem * getCollisionSystem();
	CharacterControlSystem * getCharacterControlSystem();
	NetworkSystem * getNetworkSystem();
	CursorControlSystem * getCursorControlSystem();
	BoxPhysicsSystem * getBoxPhysicsSystem();
	UIGraphicsSystem * getUIGraphicsSystem();
	UIControlSystem * getUIControlSystem();

private:
	void addToSystems(Entity* entity);

	//	Systems	
	std::map<std::string, System*> m_systems;

	//	Entity master list.
	std::vector<Entity*> m_entities;

	ScreenManager* m_screenManager;
	SDL_Renderer* m_renderer;
	const std::string RESOURCES_PATH = ".//resources//";
};
#endif // !ENTITY_MANAGER_H
