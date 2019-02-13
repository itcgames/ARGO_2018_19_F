#include "ECS\Entities\EntityManager.h"

/// <summary>
/// 
/// </summary>
/// <param name="client"></param>
EntityManager::EntityManager(Client* client) :
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
	player->addComponent(new CollisionComponent(collider, "Player"));

	if (controllable)
	{
		player->addComponent(new ControllerComponent());
		player->addComponent(new PhysicsComponent());
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
	obstacle->addComponent(new CollisionComponent(collider, "Obstacle"));

	addToSystems(obstacle);
	m_entities.push_back(obstacle);
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
	goal->addComponent(new CollisionComponent(collider, "Goal"));

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

	if (entity->getComponent("COLLISION") != nullptr)
	{
		m_collisionSystem.addEntity(entity);
	}

	if (entity->getComponent("CONTROLLER") != nullptr)
	{
		m_characterControlSystem.addEntity(entity);
	}

	if (entity->getComponent("NETWORK") != nullptr)
	{
		m_networkSystem.addEntity(entity);
	}
}
