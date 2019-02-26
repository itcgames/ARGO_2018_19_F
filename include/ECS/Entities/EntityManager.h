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
#include "ECS/Components/PlayerStateComponent.h"
#include "ECS/Components/SelectionBoxComponent.h"
//	Systems.
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/NetworkSystem.h"
#include "ECS/Systems/SelectionBoxSystem.h"
#include "ECS/Systems/CursorControlSystem.h"
#include "ECS/Systems/UIGraphicsSystem.h"
#include "ECS/Systems/UIControlSystem.h"
#include "ECS/Systems/PlayerStateSystem.h"

class EntityManager
{
public:
	EntityManager(ScreenManager* screenManager, SDL_Renderer* renderer);
	~EntityManager();

	void update(double dt);	
	void render();

	void gameLoop(double dt, bool gameInProgress, bool online);
	void placement(double dt, bool online);
	void playing(double dt, bool online);

	/// <summary>
	/// Player.
	/// </summary>
	void createPlayer(int playerNum, Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider, bool controllable, bool online);

	/// <summary>
	/// Game entities.
	/// </summary>
	void createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag = "");
	void createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag = "");

	/// <summary>
	/// Background entity.
	/// </summary>
	void createBackground(SDL_Texture* texture);

	/// <summary>
	/// Placement entities.
	/// </summary>
	void createSelectionBox();
	void createCursor(int index, Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider);

	/// <summary>
	/// Start and goal entities.
	/// </summary>
	void createStart(Vector startPosition, SDL_Texture* texture, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createGoal(Vector startPosition, SDL_Texture* texture, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);

	/// <summary>
	/// UI Elements
	/// </summary>
	void createLabel(Vector position, std::string text, SDL_Color colour, int width, int height);	
	void createImage(Vector position, SDL_Texture * texture, SDL_Rect destRect);
	void createButton(int index, bool selected, std::string goTo, Vector position, std::string text, SDL_Color colour, int width, int height);
	void createFunctionButton(Vector position, int index, bool selected, std::function<void()>  func, SDL_Texture* texture, int srcWidth, int srcHeight, int destWidth, int destHeight);

	/// <summary>
	/// Systems.
	/// </summary>
	GraphicsSystem * getGraphicsSystem();
	PhysicsSystem * getPhysicsSystem();
	CollisionSystem * getCollisionSystem();
	CharacterControlSystem * getCharacterControlSystem();
	NetworkSystem * getNetworkSystem();
	CursorControlSystem * getCursorControlSystem();
	SelectionBoxSystem * getSelectionBoxSystem();
	UIGraphicsSystem * getUIGraphicsSystem();
	UIControlSystem * getUIControlSystem();
	PlayerStateSystem * getPlayerStateSystem();

	/// <summary>
	/// Entities.
	/// </summary>
	std::vector<Entity*> getEntities();
	Entity* getEntityById(std::string id, int number = 0);
	std::vector<Entity*> getEntitiesWithTag(std::string id);

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
