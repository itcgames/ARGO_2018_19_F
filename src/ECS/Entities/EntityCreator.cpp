#include "ECS\Entities\EntityCreator.h"

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
Entity * EntityCreator::createPlayer(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider)
{
	Entity* player = new Entity();
	player->setId("player");
	player->addComponent(new PositionComponent(startPosition));
	player->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	player->addComponent(new AnimationComponent(animStart, animEnd));
	player->addComponent(new PhysicsComponent());
	player->addComponent(new CollisionComponent(collider, "Player"));
	player->addComponent(new ControllerComponent());

	return player;
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
Entity * EntityCreator::createObstacle(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* obstacle = new Entity();
	obstacle->setId("obstacle");
	obstacle->addComponent(new PositionComponent(startPosition));
	obstacle->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	obstacle->addComponent(new CollisionComponent(collider, "Obstacle"));

	return obstacle;
}

Entity * EntityCreator::createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* obstacle = new Entity();
	obstacle->setId("Platform");
	obstacle->addComponent(new PositionComponent(startPosition));
	obstacle->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	obstacle->addComponent(new CollisionComponent(collider, "Platform"));

	return obstacle;
}



/// <summary>
/// 
/// </summary>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <returns></returns>
Entity * EntityCreator::createBackground(SDL_Texture * texture, SDL_Rect srcRect)
{
	Entity* background = new Entity();
	background->setId("background");
	background->addComponent(new PositionComponent());
	background->addComponent(new GraphicsComponent(texture, srcRect, SDL2Help::InitRect(0, 0, 1600, 900)));

	return background;
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
Entity * EntityCreator::createStart(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider)
{
	Entity* start = new Entity();
	start->setId("start");
	start->addComponent(new PositionComponent(startPosition));
	start->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	start->addComponent(new AnimationComponent(animStart, animEnd));
	start->addComponent(new CollisionComponent(collider, "start"));

	return start;
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
Entity * EntityCreator::createGoal(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider)
{
	Entity* goal = new Entity();
	goal->setId("goal");
	goal->addComponent(new PositionComponent(startPosition));
	goal->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	goal->addComponent(new AnimationComponent(animStart, animEnd));
	goal->addComponent(new CollisionComponent(collider, "Goal"));

	return goal;
}
