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
	for (Entity* entity : m_entities)
	{
		for (auto component : entity->getComponents())
		{
			delete(component.second);
		}
		delete(entity);
	}
	
	for (std::pair<std::string, System*> system : m_systems)
	{
		delete(system.second);
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void EntityManager::update(double dt)
{
	for (std::pair<std::string, System*> systemPair : m_systems)
	{
		System* system = systemPair.second;
		if (system != nullptr)
		{
			system->update(dt);
		}
	}
}



/// <summary>
/// 
/// </summary>
void EntityManager::render()
{
	for (std::pair<std::string, System*> systemPair : m_systems)
	{
		System* system = systemPair.second;
		if (system != nullptr)
		{
			system->render(m_renderer);
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void EntityManager::gameLoop(double dt, bool gameInProgress, bool online)
{	
	getSelectionBoxSystem()->update(dt);
	if (gameInProgress)
	{
		playing(dt, online);
	}
	else
	{
		placement(dt, online);
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void EntityManager::placement(double dt, bool online)
{
	getCursorControlSystem()->update(dt);
	if (online)
	{
		getNetworkSystem()->update(dt);
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void EntityManager::playing(double dt, bool online)
{
	getCharacterControlSystem()->update(dt);
	getGraphicsSystem()->update(dt);
	getCollisionSystem()->update(dt);
	getPlayerStateSystem()->update(dt);
	getPhysicsSystem()->update(dt);
	if (online)
	{
		getNetworkSystem()->update(dt);
	}
}



/// <summary>
/// Adds a player entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="playerNum">The players number.</param>
/// <param name="startPosition">The players starting position.</param>
/// <param name="texture">The texture the player will use.</param>
/// <param name="srcRect">The src rectangle the texture will use.</param>
/// <param name="destRect">The destination rectangle the texture will use.</param>
/// <param name="animStart">The position of the first frame.</param>
/// <param name="animEnd">The position of the final frame.</param>
/// <param name="collider">The players collider.</param>
/// <param name="controllable">If the player is controllable or not.</param>
/// <param name="online">If game is online or not.</param>
void EntityManager::createPlayer(int playerNum, Vector startPosition, SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, Vector animStart, Vector animEnd, SDL_Rect collider, bool controllable, bool online)
{
	Entity* player = new Entity();
	player->setId("player");	
	player->addComponent(new PositionComponent(startPosition));
	player->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	player->addComponent(new AnimationComponent(animStart, animEnd));	
	player->addComponent(new CollisionComponent(collider, "player"));
	player->addComponent(new PhysicsComponent());
	player->addComponent(new PlayerStateComponent());

	if (controllable)
	{
		player->addComponent(new ControllerComponent(playerNum));
	}

	if (online)
	{
		player->addComponent(new NetworkComponent(playerNum));
	}

	addToSystems(player);
	m_entities.push_back(player);
}



/// <summary>
/// Adds a obstacle entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="startPosition">The obstacles position.</param>
/// <param name="texture">The texture the obstacle will use.</param>
/// <param name="destRect">The dest rectangle the texture will use.</param>
/// <param name="collider">The obstacles collider.</param>
/// <param name="secondaryTag">The secondary tag of the obstacle.</param>
void EntityManager::createObstacle(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag, bool animated, Vector firstFrame, Vector lastFrame)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = {0, 0, attributes.width, attributes.height};

	Entity* obstacle = new Entity();
	obstacle->setId("obstacle");
	obstacle->addComponent(new PositionComponent(startPosition));
	obstacle->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	obstacle->addComponent(new CollisionComponent(collider, "obstacle", secondaryTag));

	if (animated)
	{
		obstacle->addComponent(new AnimationComponent(firstFrame, lastFrame));
	}

	addToSystems(obstacle);
	m_entities.push_back(obstacle);
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <param name="secondaryTag"></param>
/// <param name="animated"></param>
/// <param name="firstFrame"></param>
/// <param name="lastFrame"></param>
Entity* EntityManager::returnObstacle(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag, bool animated, Vector firstFrame, Vector lastFrame)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* obstacle = new Entity();
	obstacle->setId("obstacle");
	obstacle->addComponent(new PositionComponent(startPosition));
	obstacle->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	obstacle->addComponent(new CollisionComponent(collider, "obstacle", secondaryTag));

	if (animated)
	{
		obstacle->addComponent(new AnimationComponent(firstFrame, lastFrame));
	}

	addToSystems(obstacle);
	m_entities.push_back(obstacle);
	return obstacle;
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="dest"></param>
/// <param name="collider"></param>
/// <param name="firstFrame"></param>
/// <param name="lastFrame"></param>
/// <returns></returns>
Entity * EntityManager::returnEmitter(Vector startPosition, SDL_Texture * texture, SDL_Rect dest, SDL_Rect collider, Vector firstFrame, Vector lastFrame)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* emitter = new Entity();
	emitter->setId("emitter");
	emitter->addComponent(new PositionComponent(startPosition));
	emitter->addComponent();

	return emitter;
}



/// <summary>
/// Adds a platform entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="startPosition">The platforms position.</param>
/// <param name="texture">The texture the platform will use.</param>
/// <param name="destRect">the dest rectangle the texture will use.</param>
/// <param name="collider">The platforms collider.</param>
/// <param name="secondaryTag">The secondary tag of the platform.</param>
void EntityManager::createPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag, bool animated, Vector firstFrame, Vector lastFrame)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* platform = new Entity();
	platform->setId("platform");
	platform->addComponent(new PositionComponent(startPosition));
	platform->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	platform->addComponent(new CollisionComponent(collider, "platform", secondaryTag));

	if (animated)
	{
		platform->addComponent(new AnimationComponent(firstFrame, lastFrame));
	}

	addToSystems(platform);
	m_entities.push_back(platform);
}



/// <summary>
/// 
/// </summary>
/// <param name="startPosition"></param>
/// <param name="texture"></param>
/// <param name="destRect"></param>
/// <param name="collider"></param>
/// <param name="secondaryTag"></param>
/// <param name="animated"></param>
/// <param name="firstFrame"></param>
/// <param name="lastFrame"></param>
Entity* EntityManager::returnPlatform(Vector startPosition, SDL_Texture * texture, SDL_Rect destRect, SDL_Rect collider, std::string secondaryTag, bool animated, Vector firstFrame, Vector lastFrame)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* platform = new Entity();
	platform->setId("platform");
	platform->addComponent(new PositionComponent(startPosition));
	platform->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	platform->addComponent(new CollisionComponent(collider, "platform", secondaryTag));

	if (animated)
	{
		platform->addComponent(new AnimationComponent(firstFrame, lastFrame));
	}

	addToSystems(platform);
	m_entities.push_back(platform);
	return platform;
}



/// <summary>
/// Adds a background entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="texture">The texture the background will use.</param>
/// <returns></returns>
void EntityManager::createBackground(SDL_Texture * texture)
{
	TextureAttributes textureAttributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, textureAttributes.width, textureAttributes.height};
	SDL_Rect destRect = { 0, 0, 1600, 900};

	Entity* background = new Entity();
	background->setId("background");
	background->addComponent(new PositionComponent(Vector(0, 0)));
	background->addComponent(new GraphicsComponent(texture, srcRect, destRect));

	addToSystems(background);
	m_entities.push_back(background);
}



/// <summary>
/// Adds a selection box entity to the relevant systems and the master entity list.
/// </summary>
void EntityManager::createSelectionBox()
{
	Entity* pauseBox = new Entity();
	pauseBox->setId("selection_box");
	pauseBox->addComponent(new PositionComponent(Vector(-100, -1000)));
	pauseBox->addComponent(new GraphicsComponent(SDL2Help::LoadTexture(RESOURCES_PATH + "Backgrounds//WoodenBack.png", m_renderer), { 0, 0, 500, 700 }, { 0 ,0, 1800, 1100}));
	pauseBox->addComponent(new SelectionBoxComponent(true));

	addToSystems(pauseBox);
	m_entities.push_back(pauseBox);
}



/// <summary>
/// Adds a cursor entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="index">The index of the player that will be controlling the cursor.</param>
/// <param name="startPosition">The starting position of the cursor.</param>
/// <param name="texture">The texture the cursor will use.</param>
/// <param name="destRect">The dest rectangle the texture will use.</param>
/// <param name="collider">The cursor's collider.</param>
/// <returns></returns>
void EntityManager::createCursor(int index, Vector startPosition, SDL_Texture* texture, SDL_Rect destRect, SDL_Rect collider)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* cursor = new Entity();
	cursor->setId("cursor");
	cursor->addComponent(new PositionComponent(startPosition));
	cursor->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	cursor->addComponent(new CollisionComponent(collider, "cursor"));
	cursor->addComponent(new ControllerComponent(index));

	addToSystems(cursor);
	m_entities.push_back(cursor);
}



/// <summary>
/// Adds a goal entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="startPosition">The position of the goal point.</param>
/// <param name="texture">The texture the goal point will use.</param>
/// <param name="destRect">The dest rectangle the texture will use.</param>
/// <param name="collider">The goal points collider.</param>
/// <returns></returns>
void EntityManager::createGoal(Vector startPosition, SDL_Rect collider, SDL_Texture * texture, SDL_Rect destRect)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* goal = new Entity();
	goal->setId("goal");
	goal->addComponent(new PositionComponent(startPosition));
	if (texture != nullptr)
	{
		goal->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	}	
	goal->addComponent(new CollisionComponent(collider, "goal"));

	addToSystems(goal);
	m_entities.push_back(goal);
}



/// <summary>
/// Adds a label entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="position">The position of the label.</param>
/// <param name="text">The text on the label.</param>
/// <param name="colour">The colour of the text.</param>
/// <param name="width">The width of the label.</param>
/// <param name="height">The height of the label.</param>
void EntityManager::createLabel(Vector position, std::string text, SDL_Color colour, int width, int height)
{
	const char* string = text.c_str();
	Entity* label = new Entity();
	label->setId("label");
	label->addComponent(new PositionComponent(position));
	label->addComponent(new TextComponent(string, width, height, colour));

	addToSystems(label);
	m_entities.push_back(label);
}



/// <summary>
/// Adds a image entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="position">The position of the image.</param>
/// <param name="texture">The texture the image will use.s</param>
/// <param name="destRect">The dest rectangle the texture will use.</param>
void EntityManager::createImage(Vector position, SDL_Texture * texture, SDL_Rect destRect)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* image = new Entity();
	image->setId("image");
	image->addComponent(new PositionComponent(position));
	image->addComponent(new GraphicsComponent(texture, srcRect, destRect));

	addToSystems(image);
	m_entities.push_back(image);
}



/// <summary>
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="texture"></param>
/// <param name="destRect"></param>
void EntityManager::createAnimatedImage(Vector position, SDL_Texture * texture, SDL_Rect destRect, Vector firstFrame, Vector lastFrame)
{
	TextureAttributes attributes = SDL2Help::getTextureAttributes(texture);
	SDL_Rect srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* image = new Entity();
	image->setId("animImage");
	image->addComponent(new PositionComponent(position));
	image->addComponent(new GraphicsComponent(texture, srcRect, destRect));
	image->addComponent(new AnimationComponent(firstFrame, lastFrame));

	addToSystems(image);
	m_entities.push_back(image);
}



/// <summary>
/// Adds a button entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="index">The buttons index.</param>
/// <param name="selected">If the button starts selected.</param>
/// <param name="goTo">The screen to go to on click.</param>
/// <param name="position">The position of the button.</param>
/// <param name="text">The text displayed on the button.</param>
/// <param name="colour">The colour of the text.</param>
/// <param name="width">The width of the button.</param>
/// <param name="height">The height of the button.</param>
void EntityManager::createButton(int index, bool selected, std::string goTo, Vector position, std::string text, SDL_Color colour, int width, int height)
{
	TextureAttributes attributes;

	Texture highlight;
	highlight.texture = SDL2Help::LoadTexture(RESOURCES_PATH + "buttons//Rectangle//RectangleHighlight.png", m_renderer);
	attributes = SDL2Help::getTextureAttributes(highlight.texture);
	highlight.srcRect = { 0, 0, attributes.width, attributes.height };

	Texture normal;
	normal.texture = SDL2Help::LoadTexture(RESOURCES_PATH + "buttons//Rectangle//Rectangle.png", m_renderer);
	attributes = SDL2Help::getTextureAttributes(normal.texture);
	normal.srcRect = { 0, 0, attributes.width, attributes.height };

	Texture pressed;
	pressed.texture = SDL2Help::LoadTexture(RESOURCES_PATH + "buttons//Rectangle//RectanglePressed.png", m_renderer);
	attributes = SDL2Help::getTextureAttributes(pressed.texture);
	pressed.srcRect = { 0, 0, attributes.width, attributes.height };

	Entity* button = new Entity();
	button->setId("button");
	button->addComponent(new PositionComponent(position));
	button->addComponent(new TextComponent(text, width / 2, height / 2, colour));
	button->addComponent(new GraphicsComponent(normal.texture, { 0, 0, attributes.width, attributes.height }, { 0, 0, width, height }, 0));
	button->addComponent(new ControllerComponent(0));
	button->addComponent(new ButtonComponent(index, selected, goTo, normal, highlight, pressed));

	addToSystems(button);
	m_entities.push_back(button);
}



/// <summary>
/// Adds a function button entity to the relevant systems and the master entity list.
/// </summary>
/// <param name="position">The position of the function button.</param>
/// <param name="index">The index of the function button.</param>
/// <param name="selected">If the function button starts selected or not.</param>
/// <param name="func">The function that is called on click.</param>
/// <param name="texture">The texture the button will use.</param>
/// <param name="srcWidth">The src width the texture will use.</param>
/// <param name="srcHeight">The src height the texture will use.</param>
/// <param name="destWidth">The dest width the texture will use.</param>
/// <param name="destHeight">The dest height the texture will use.</param>
void EntityManager::createFunctionButton(Vector position, int index, bool selected, std::function<void()> func, SDL_Texture * texture, int srcWidth, int srcHeight, int destWidth, int destHeight)
{
	Entity* button = new Entity();
	button->setId("funcButton");
	button->addComponent(new PositionComponent(position));
	button->addComponent(new GraphicsComponent(texture, { 0, 0, srcWidth, srcHeight }, { 0, 0, destWidth, destHeight }));
	button->addComponent(new FuncButtonComponent(index, selected, func, {0, 0, destWidth, destHeight}));
	button->addComponent(new ControllerComponent(0));

	addToSystems(button);
	m_entities.push_back(button);
}



/// <summary>
/// Returns the GraphicsSystem.
/// </summary>
/// <returns></returns>
GraphicsSystem * EntityManager::getGraphicsSystem()
{
	return (GraphicsSystem*)m_systems["GRAPHICS"];
}



/// <summary>
/// Returns the PhysicsSystem.
/// </summary>
/// <returns></returns>
PhysicsSystem * EntityManager::getPhysicsSystem()
{
	return (PhysicsSystem*)m_systems["PHYSICS"];
}



/// <summary>
/// Returns the CollisionSystem.
/// </summary>
/// <returns></returns>
CollisionSystem * EntityManager::getCollisionSystem()
{
	return (CollisionSystem*) m_systems["COLLISION"];
}



/// <summary>
/// Returns the CharacterControlSystem.
/// </summary>
/// <returns></returns>
CharacterControlSystem * EntityManager::getCharacterControlSystem()
{
	return (CharacterControlSystem*) m_systems["CHARACTER_CONTROLLER"];
}



/// <summary>
/// Returns the NetworkSystem.
/// </summary>
/// <returns></returns>
NetworkSystem * EntityManager::getNetworkSystem()
{
	return (NetworkSystem*) m_systems["NETWORK"];
}



/// <summary>
/// Returns the CursorControlSystem.
/// </summary>
/// <returns></returns>
CursorControlSystem * EntityManager::getCursorControlSystem()
{
	return (CursorControlSystem*) m_systems["CURSOR_CONTROLLER"];
}



/// <summary>
/// Returns the SelectionBoxSystem.
/// </summary>
/// <returns></returns>
SelectionBoxSystem * EntityManager::getSelectionBoxSystem()
{
	return (SelectionBoxSystem*) m_systems["SELECTION_BOX"];
}



/// <summary>
/// Returns the UIGraphicsSystem.
/// </summary>
/// <returns></returns>
UIGraphicsSystem * EntityManager::getUIGraphicsSystem()
{
	return (UIGraphicsSystem*) m_systems["UI_GRAPHICS"];
}



/// <summary>
/// Returns the UIControlSystem.
/// </summary>
/// <returns></returns>
UIControlSystem * EntityManager::getUIControlSystem()
{
	return (UIControlSystem*) m_systems["UI_CONTROL"];
}



/// <summary>
/// Returns the PlayerStateSystem.
/// </summary>
/// <returns></returns>
PlayerStateSystem * EntityManager::getPlayerStateSystem()
{
	return (PlayerStateSystem*)m_systems["PLAYER_STATE"];
}



/// <summary>
/// Returns a vector containing all entities.
/// </summary>
/// <returns></returns>
std::vector<Entity*> EntityManager::getEntities()
{
	return m_entities;
}



/// <summary>
/// Returns an entity with the id.
/// </summary>
/// <param name="id">the id of the entity.</param>
/// <param name="number">how many entities with that tag to ignore.</param>
/// <returns>Returns either the entity if it was found or nullptr</returns>
Entity * EntityManager::getEntityById(std::string id, int number)
{
	std::vector<Entity*>::iterator iter = m_entities.begin();
	Entity* entity = nullptr;
	int ignored = 0;
	while (iter++ != m_entities.end() && entity == nullptr)
	{
		if (ignored < number)
		{
			++ignored;
		}
		else if ((*iter)->getId() == id)
		{
			entity = (*iter);
		}
	}
	return entity;
}



/// <summary>
/// Returns all entities with the passed tag.
/// </summary>
/// <param name="id">the id of the entity.</param>
/// <returns>Returns a vector of entities that has the tag.</returns>
std::vector<Entity*> EntityManager::getEntitiesWithTag(std::string id)
{
	std::vector<Entity*>::iterator iter = m_entities.begin();
	std::vector<Entity*> entities;
	while (iter != m_entities.end())
	{
		if ((*iter)->getId() == id)
		{
			entities.push_back((*iter));
		}
		iter++;
	}
	return entities;
}



/// <summary>
/// Removes the passed entity from the master entity list and from all associated systems.
/// </summary>
/// <param name="entity"></param>
void EntityManager::removeEntity(Entity * entity)
{
	m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entity), m_entities.end());

	for (std::pair<std::string, System*> pair : m_systems)
	{
		System* system = pair.second;
		system->removeEntity(entity);
	}
}



/// <summary>
/// 
/// </summary>
void EntityManager::addToSystems(Entity* entity)
{
	/// <summary>
	/// Add entity to the GraphicsSystem.
	/// </summary>
	if (entity->getComponent("GRAPHICS") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["GRAPHICS"] == nullptr)
		{
			m_systems["GRAPHICS"] = new GraphicsSystem();
		}

		//	Add entity to system.
		m_systems["GRAPHICS"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the UIGraphicsSystem
	/// </summary>
	if (entity->getComponent("TEXT") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["UI_GRAPHICS"] == nullptr)
		{
			m_systems["UI_GRAPHICS"] = new UIGraphicsSystem();
		}

		//	Add entity to system.
		m_systems["UI_GRAPHICS"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the UIControlSystem.
	/// </summary>
 	if (entity->getComponent("BUTTON") != nullptr || entity->getComponent("FUNC_BUTTON") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["UI_CONTROL"] == nullptr)
		{
			m_systems["UI_CONTROL"] = new UIControlSystem(m_screenManager);
		}

		//	Add entity to system.
		m_systems["UI_CONTROL"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the PhysicsSystem.
	/// </summary>
	if (entity->getComponent("PHYSICS") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["PHYSICS"] == nullptr)
		{
			m_systems["PHYSICS"] = new PhysicsSystem();
		}

		//	Add entity to system.
		m_systems["PHYSICS"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the SelectionBoxSystem.
	/// </summary>
	if (entity->getComponent("SELECTION_BOX") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["SELECTION_BOX"] == nullptr)
		{
			m_systems["SELECTION_BOX"] = new SelectionBoxSystem();
		}

		//	Add entity to system.
		m_systems["SELECTION_BOX"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the CollisionSystem.
	/// </summary>
	if (entity->getComponent("COLLISION") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["COLLISION"] == nullptr)
		{
			m_systems["COLLISION"] = new CollisionSystem();
		}

		//	Add entity to system.
		m_systems["COLLISION"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the CharacterControlSystem and CursorControlSystem.
	/// </summary>
	if (entity->getComponent("CONTROLLER") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["CHARACTER_CONTROLLER"] == nullptr)
		{
			m_systems["CHARACTER_CONTROLLER"] = new CharacterControlSystem();
		}

		//	Add entity to system.
		m_systems["CHARACTER_CONTROLLER"]->addEntity(entity);

		//	Create system if it hasn't been created yet.
		if (m_systems["CURSOR_CONTROLLER"] == nullptr)
		{
			m_systems["CURSOR_CONTROLLER"] = new CursorControlSystem();
		}
		
		//	Add entity to system.
		m_systems["CURSOR_CONTROLLER"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to the NetworkSystem
	/// </summary>
	if (entity->getComponent("NETWORK") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["NETWORK"] == nullptr)
		{
			m_systems["NETWORK"] = new NetworkSystem(m_screenManager->getClient());
		}

		//	Add entity to system.
		m_systems["NETWORK"]->addEntity(entity);
	}

	/// <summary>
	/// Add entity to PlayerStateSystem.
	/// </summary>
	if (entity->getComponent("PLAYER_STATE") != nullptr)
	{
		//	Create system if it hasn't been created yet.
		if (m_systems["PLAYER_STATE"] == nullptr)
		{
			m_systems["PLAYER_STATE"] = new PlayerStateSystem();
		}

		//	Add entity to system.
		m_systems["PLAYER_STATE"]->addEntity(entity);
	}
}
