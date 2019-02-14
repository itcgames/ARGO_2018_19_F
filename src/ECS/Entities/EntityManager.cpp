#include "ECS\Entities\EntityManager.h"

/// <summary>
/// 
/// </summary>
/// <param name="client"></param>
EntityManager::EntityManager(std::pair<std::string, Client*> client) :
	m_networkSystem(client)
{
}



/// <summary>
/// 
/// </summary>
EntityManager::~EntityManager()
{
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="animStart"></param>
/// <param name="animEnd"></param>
/// <param name="collider"></param>
/// <returns></returns>
void EntityManager::createPlayer(int playerNum, Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider, bool controllable)
{
	Entity* player = new Entity();
	player->setId("player");
	player->addComponent(new NetworkComponent(playerNum));
	player->addComponent(new PositionComponent(startPosition));
	player->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	player->addComponent(new AnimationComponent(animStart, animEnd));	
	player->addComponent(new CollisionComponent(collider, "player"));
	player->addComponent(new PhysicsComponent());

	if (controllable)
	{
		player->addComponent(new ControllerComponent());
	}

	addToSystems(player);
	m_entities.push_back(player);
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <returns></returns>
void EntityManager::createObstacle(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* obstacle = new Entity();
	obstacle->setId("obstacle");
	obstacle->addComponent(new PositionComponent(startPosition));
	obstacle->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	obstacle->addComponent(new CollisionComponent(collider, "obstacle"));

	addToSystems(obstacle);
	m_entities.push_back(obstacle);
}

/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <returns></returns>
void EntityManager::createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* platform = new Entity();
	platform->setId("platform");
	platform->addComponent(new PositionComponent(startPosition));
	platform->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	platform->addComponent(new CollisionComponent(collider, "platform"));

	addToSystems(platform);
	m_entities.push_back(platform);
}



/// <summary>
/// 
/// </summary>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <returns></returns>
void EntityManager::createBackground(SDL_Texture * texture, SDL_Rect srcRect)
{
	Entity* background = new Entity();
	background->setId("background");
	background->addComponent(new PositionComponent());
	background->addComponent(new GraphicsComponent(texture, srcRect, SDL2Help::InitRect(0, 0, 1600, 900)));

	addToSystems(background);
	m_entities.push_back(background);
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <returns></returns>
void EntityManager::createSelectionBox(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	Entity* pauseBox = new Entity();
	pauseBox->setId("pauseBox");
	pauseBox->addComponent(new PositionComponent(startPosition));
	pauseBox->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	pauseBox->addComponent(new BoxPhysicsComponent());
	pauseBox->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 0, 0), "pauseBox"));
	pauseBox->addComponent(new ControllerComponent(0));

	addToSystems(pauseBox);
	m_entities.push_back(pauseBox);
}



/// <summary>
/// The cursor for the selection rounds
/// The cursor is used to pick up an obstacle
/// The cursor is used to place an obstacle
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <returns></returns>
void EntityManager::createCursor(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* cursor = new Entity();
	cursor->setId("cursor");
	cursor->addComponent(new PositionComponent(startPosition));
	cursor->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	cursor->addComponent(new CollisionComponent(collider, "cursor"));
	cursor->addComponent(new ControllerComponent(0));
	//cursor->addComponent(new PhysicsComponent());

	addToSystems(cursor);
	m_entities.push_back(cursor);
}



/// <summary>
/// function to create a starting point
/// Re usable for each level
/// Player entity is always initialised to the 
/// create start position.
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="animStart"></param>
/// <param name="animEnd"></param>
/// <param name="collider"></param>
/// <returns></returns>
void EntityManager::createStart(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider)
{
	Entity* start = new Entity();
	start->setId("start");
	start->addComponent(new PositionComponent(startPosition));
	start->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	start->addComponent(new AnimationComponent(animStart, animEnd));
	start->addComponent(new CollisionComponent(collider, "start"));

	addToSystems(start);
	m_entities.push_back(start);
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="animStart"></param>
/// <param name="animEnd"></param>
/// <param name="collider"></param>
/// <returns></returns>
void EntityManager::createGoal(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider)
{
	Entity* goal = new Entity();
	goal->setId("goal");
	goal->addComponent(new PositionComponent(startPosition));
	goal->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	goal->addComponent(new AnimationComponent(animStart, animEnd));
	goal->addComponent(new CollisionComponent(collider, "goal"));

	addToSystems(goal);
	m_entities.push_back(goal);
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
GraphicsSystem * EntityManager::getGraphicsSystem()
{
	return &m_graphicsSystem;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
PhysicsSystem * EntityManager::getPhysicsSystem()
{
	return &m_physicsSystem;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
CollisionSystem * EntityManager::getCollisionSystem()
{
	return &m_collisionSystem;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
CharacterControlSystem * EntityManager::getCharacterControlSystem()
{
	return &m_characterControlSystem;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
NetworkSystem * EntityManager::getNetworkSystem()
{
	return &m_networkSystem;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
CursorControlSystem * EntityManager::getCursorControlSystem()
{
	return &m_cursorControlSystem;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
BoxPhysicsSystem * EntityManager::getBoxPhysicsSystem()
{
	return &m_boxPhysicsSystem;
}



/// <summary>
/// 
/// </summary>
void EntityManager::addToSystems(Entity* entity)
{
	if (entity->getComponent("GRAPHICS") != nullptr)
	{
		m_graphicsSystem.addEntity(entity);
	}

	if (entity->getComponent("PHYSICS") != nullptr)
	{
		m_physicsSystem.addEntity(entity);
	}

	if (entity->getComponent("BOXPHYSICS") != nullptr)
	{
		m_boxPhysicsSystem.addEntity(entity);
	}

	if (entity->getComponent("COLLISION") != nullptr)
	{
		m_collisionSystem.addEntity(entity);
	}

	if (entity->getComponent("CONTROLLER") != nullptr)
	{
		m_characterControlSystem.addEntity(entity);
		m_cursorControlSystem.addEntity(entity);
	}

	if (entity->getComponent("NETWORK") != nullptr)
	{
		m_networkSystem.addEntity(entity);
	}
}
