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
#include "ECS/Components/PlacedComponent.h"
//	Systems.
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/NetworkSystem.h"
#include "ECS/Systems/SelectionBoxSystem.h"
#include "ECS/Systems/CursorControlSystem.h"
#include "ECS/Systems/UIGraphicsSystem.h"
#include "ECS/Systems/AISystem.h"
#include "ECS/Systems/UIControlSystem.h"
#include "ECS/Systems/PlayerStateSystem.h"
#include "ECS/Systems/AICursorControlSystem.h"
#include "ECS/Systems/ObjectPlacedSystem.h"

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
	void createObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag = "", bool animated = false, Vector firstFrame = { 0, 0 }, Vector lastFrame = {0, 0});
	Entity* returnObstacle(Vector startPosition, SDL_Texture* texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag = "", bool animated = false, Vector firstFrame = { 0, 0 }, Vector lastFrame = { 0, 0 });

	Entity* returnEmitter(Vector startPosition, SDL_Texture* texture, SDL_Rect dest, SDL_Rect collider, Vector firstFrame, Vector lastFrame);
	
	void createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag = "", bool animated = false, Vector firstFrame = { 0, 0 }, Vector lastFrame = { 0, 0 });
	Entity* returnPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag = "", bool animated = false, Vector firstFrame = { 0, 0 }, Vector lastFrame = { 0, 0 });

	/// <summary>
	/// Background entity.
	/// </summary>
	void createBackground(SDL_Texture* texture);

	/// <summary>
	/// Placement entities.
	/// </summary>
	void createSelectionBox();
	void createCursor(int index);
	void createAI(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider);
	void createAICursor(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider);

	/// <summary>
	/// Goal entity.
	/// </summary>
	void createGoal(Vector startPosition, SDL_Rect collider, SDL_Texture* texture = nullptr, SDL_Rect destRect = {0, 0, 0});

	/// <summary>
	/// UI Elements
	/// </summary>
	void createLabel(Vector position, std::string text, SDL_Color colour, int width, int height);	
	void createImage(Vector position, SDL_Texture * texture, SDL_Rect destRect);
	void createAnimatedImage(Vector position, SDL_Texture * texture, SDL_Rect destRect, Vector firstFrame, Vector lastFrame);
	void createButton(int index, bool selected, std::string goTo, Vector position, std::string text, SDL_Color colour, int width, int height);
	void createFunctionButton(Vector position, int index, bool selected, std::function<void()>  func, SDL_Texture* texture, int srcWidth, int srcHeight, int destWidth, int destHeight);

	/// <summary>
	/// Systems.
	/// </summary>
	GraphicsSystem*			 getGraphicsSystem();
	PhysicsSystem*			 getPhysicsSystem();
	CollisionSystem*		 getCollisionSystem();
	CharacterControlSystem*  getCharacterControlSystem();
	NetworkSystem*			 getNetworkSystem();
	CursorControlSystem*	 getCursorControlSystem();
	SelectionBoxSystem*		 getSelectionBoxSystem();
	UIGraphicsSystem*		 getUIGraphicsSystem();
	UIControlSystem*		 getUIControlSystem();
	PlayerStateSystem*		 getPlayerStateSystem();
	AISystem*				 getAISystem();
	AICursorControlSystem*	 getAICursorControlSystem();
	ObjectPlacedSystem*		 getObjectPlacedSystem();

	/// <summary>
	/// Entities.
	/// </summary>
	std::vector<Entity*> getEntities();
	Entity* getEntityById(std::string id, int number = 0);
	std::vector<Entity*> getEntitiesWithTag(std::string id);
	void removeEntity(Entity* entity);

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
