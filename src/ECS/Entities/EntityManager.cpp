#include "ECS\Entities\EntityManager.h"

/// <summary>
/// 
/// </summary>
EntityManager::EntityManager(ScreenManager* screenManager, SDL_Renderer* renderer) :
	m_screenManager(screenManager),
	m_renderer(renderer)
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
void EntityManager::createSpring(Vector position, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect, SDL_Rect collider)
{
	Entity * spring = new Entity();
	spring->setId("springboard");
	spring->addComponent(new PositionComponent(position));
	spring->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	spring->addComponent(new CollisionComponent(collider, "springboard"));

	addToSystems(spring);
	m_entities.push_back(spring);
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
/// <param name="position"></param>
/// <param name="text"></param>
/// <param name="colour"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void EntityManager::createLabel(Vector position, std::string text, SDL_Color colour, int width, int height)
{
	const char* string = text.c_str();
	Entity* label = new Entity();
	label->addComponent(new PositionComponent(position));
	label->addComponent(new TextComponent(string, width, height, colour));

	addToSystems(label);
	m_entities.push_back(label);
}



/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="texture"></param>
/// <param name="src"></param>
/// <param name="text"></param>
/// <param name="colour"></param>
/// <param name="width"></param>
/// <param name="height"></param>
void EntityManager::createButton(int index, bool selected, std::string goTo, Vector position, std::string text, SDL_Color colour, int width, int height)
{
	TextureAttributes attributes;

	Texture highlight;
	highlight.texture = SDL2Help::LoadTexture(RESOURCES_PATH + "buttons//RectangleHighlight.png", m_renderer);
	attributes = SDL2Help::getTextureAttributes(highlight.texture);
	highlight.srcRect = { 0, 0, attributes.width, attributes.height };
	
	Texture normal;
	normal.texture = SDL2Help::LoadTexture(RESOURCES_PATH + "buttons//Rectangle.png", m_renderer);	
	attributes = SDL2Help::getTextureAttributes(normal.texture);
	normal.srcRect = { 0, 0, attributes.width, attributes.height };

	Texture pressed;
	pressed.texture = SDL2Help::LoadTexture(RESOURCES_PATH + "buttons//RectanglePressed.png", m_renderer);
	attributes = SDL2Help::getTextureAttributes(pressed.texture);
	pressed.srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* button = new Entity();
	button->addComponent(new PositionComponent(position));
	button->addComponent(new TextComponent(text, width / 2, height / 2, colour));
	button->addComponent(new GraphicsComponent(normal.texture, {0, 0, attributes.width, attributes.height}, { 0, 0, width, height }, 0));
	button->addComponent(new ControllerComponent(0));
	button->addComponent(new UIComponent(index, selected, goTo, normal, highlight, pressed));

	addToSystems(button);
	m_entities.push_back(button);
}



/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="texture"></param>
/// <param name="destRect"></param>
void EntityManager::createImage(Vector position, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	Entity* image = new Entity();
	image->addComponent(new PositionComponent(position));
	image->addComponent(new GraphicsComponent(texture, srcRect, destRect));

	addToSystems(image);
	m_entities.push_back(image);
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
GraphicsSystem * EntityManager::getGraphicsSystem()
{
	return (GraphicsSystem*)m_systems["GRAPHICS"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
PhysicsSystem * EntityManager::getPhysicsSystem()
{
	return (PhysicsSystem*)m_systems["PHYSICS"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
CollisionSystem * EntityManager::getCollisionSystem()
{
	return (CollisionSystem*) m_systems["COLLISION"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
CharacterControlSystem * EntityManager::getCharacterControlSystem()
{
	return (CharacterControlSystem*) m_systems["CHARACTER_CONTROLLER"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
NetworkSystem * EntityManager::getNetworkSystem()
{
	return (NetworkSystem*) m_systems["NETWORK"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
CursorControlSystem * EntityManager::getCursorControlSystem()
{
	return (CursorControlSystem*) m_systems["CURSOR_CONTROLLER"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
BoxPhysicsSystem * EntityManager::getBoxPhysicsSystem()
{
	return (BoxPhysicsSystem*) m_systems["BOXPHYSICS"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
UIGraphicsSystem * EntityManager::getUIGraphicsSystem()
{
	return (UIGraphicsSystem*) m_systems["UI_GRAPHICS"];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
UIControlSystem * EntityManager::getUIControlSystem()
{
	return (UIControlSystem*) m_systems["UI_CONTROL"];
}



/// <summary>
/// 
/// </summary>
void EntityManager::addToSystems(Entity* entity)
{
	if (entity->getComponent("GRAPHICS") != nullptr)
	{
		if (m_systems["GRAPHICS"] == nullptr)
		{
			m_systems["GRAPHICS"] = new GraphicsSystem();
		}

		m_systems["GRAPHICS"]->addEntity(entity);
	}

	if (entity->getComponent("TEXT") != nullptr)
	{
		if (m_systems["UI_GRAPHICS"] == nullptr)
		{
			m_systems["UI_GRAPHICS"] = new UIGraphicsSystem();
		}

		m_systems["UI_GRAPHICS"]->addEntity(entity);
	}

	if (entity->getComponent("UI") != nullptr)
	{
		if (m_systems["UI_CONTROL"] == nullptr)
		{
			m_systems["UI_CONTROL"] = new UIControlSystem(m_screenManager);
		}

		m_systems["UI_CONTROL"]->addEntity(entity);
	}

	if (entity->getComponent("PHYSICS") != nullptr)
	{
		if (m_systems["PHYSICS"] == nullptr)
		{
			m_systems["PHYSICS"] = new PhysicsSystem();
		}

		m_systems["PHYSICS"]->addEntity(entity);
	}

	if (entity->getComponent("BOXPHYSICS") != nullptr)
	{
		if (m_systems["BOXPHYSICS"] == nullptr)
		{
			m_systems["BOXPHYSICS"] = new BoxPhysicsSystem();
		}

		m_systems["BOXPHYSICS"]->addEntity(entity);
	}

	if (entity->getComponent("COLLISION") != nullptr)
	{
		if (m_systems["COLLISION"] == nullptr)
		{
			m_systems["COLLISION"] = new CollisionSystem();
		}

		m_systems["COLLISION"]->addEntity(entity);
	}

	if (entity->getComponent("CONTROLLER") != nullptr)
	{
		if (m_systems["CHARACTER_CONTROLLER"] == nullptr)
		{
			m_systems["CHARACTER_CONTROLLER"] = new CharacterControlSystem();
		}

		m_systems["CHARACTER_CONTROLLER"]->addEntity(entity);

		if (m_systems["CURSOR_CONTROLLER"] == nullptr)
		{
			m_systems["CURSOR_CONTROLLER"] = new CursorControlSystem();
		}
		
		m_systems["CURSOR_CONTROLLER"]->addEntity(entity);
	}

	if (entity->getComponent("NETWORK") != nullptr)
	{
		if (m_systems["NETWORK"] == nullptr)
		{
			m_systems["NETWORK"] = new NetworkSystem(m_screenManager->getClient());
		}

		m_systems["NETWORK"]->addEntity(entity);
	}
}
