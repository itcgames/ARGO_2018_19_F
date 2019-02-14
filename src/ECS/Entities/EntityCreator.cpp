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
	player->addComponent(new CollisionComponent(collider, "player"));
	player->addComponent(new ControllerComponent(0));

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

/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <returns></returns>
Entity * EntityCreator::createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* platform = new Entity();
	platform->setId("platform");
	platform->addComponent(new PositionComponent(startPosition));
	platform->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	platform->addComponent(new CollisionComponent(collider, "platform"));

	return platform;
}


/// <summary>
/// Spring component
/// It will make the player jump on collision
/// The Spring will animate on jump
/// It takes the following paramaters
/// </summary>
/// <param name="position"></param>
/// <param name="texture"></param>
/// <param name="srcRect"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <returns></returns>
Entity * EntityCreator::createSpring(Vector position, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity * spring = new Entity();
	spring->setId("springboard");
	spring->addComponent(new PositionComponent(position));
	spring->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	spring->addComponent(new CollisionComponent(collider, "springboard"));

	return spring;
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
/// <returns></returns>
Entity* EntityCreator::createSelectionBox(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	Entity* pauseBox = new Entity();
	pauseBox->setId("pauseBox");
	pauseBox->addComponent(new PositionComponent(startPosition));
	pauseBox->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	pauseBox->addComponent(new BoxPhysicsComponent());
	pauseBox->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 0, 0), "pauseBox"));
	pauseBox->addComponent(new ControllerComponent(0));

	return pauseBox;
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
Entity* EntityCreator::createCursor(Vector startPosition, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity* cursor = new Entity();
	cursor->setId("cursor");
	cursor->addComponent(new PositionComponent(startPosition));
	cursor->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	cursor->addComponent(new CollisionComponent(collider, "cursor"));
	cursor->addComponent(new ControllerComponent(0));
	//cursor->addComponent(new PhysicsComponent());

	return cursor;
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
