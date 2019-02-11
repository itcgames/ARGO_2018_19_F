#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_startPos(100,800)
{
	m_screenID = "Play";

	SDL_Texture* playerTexture = SDL2Help::LoadTexture(m_resourcesPath + "grid.png", m_renderer); // testing
	SDL_Texture* flagTexture = SDL2Help::LoadTexture(m_resourcesPath + "flags.png", m_renderer);
	SDL_Texture* blockTexture = SDL2Help::LoadTexture(m_resourcesPath + "woodBlock.png", m_renderer);

	
	//	Create player entity.
	Entity* player = new Entity();
	player->addComponent(new PositionComponent(m_startPos));
	player->addComponent(new GraphicsComponent(playerTexture, SDL2Help::InitRect(0, 85, 85, 85), SDL2Help::InitRect(0, 0, 32, 32)));
	player->addComponent(new AnimationComponent(new Vector(0,0,0), new Vector(5,1,0)));
	player->addComponent(new PhysicsComponent());
	player->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 32, 32), "Player"));
	player->addComponent(new ControllerComponent());
	m_entities.push_back(player);

	// Level Obstacle Entity
	Entity* obstacle = new Entity();
	obstacle->addComponent(new PositionComponent(Vector(600, 700, 0)));
	obstacle->addComponent(new GraphicsComponent(blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 100, 200)));
	obstacle->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 100, 200), "Obstacle"));
	m_entities.push_back(obstacle);

	//	Create goal entity.
	Entity* goal = new Entity();
	goal->addComponent(new PositionComponent(Vector(1400, 800)));
	goal->addComponent(new GraphicsComponent(flagTexture, SDL2Help::InitRect(0, 0, 158, 314), SDL2Help::InitRect(0, 0, 50, 100)));
	goal->addComponent(new AnimationComponent(new Vector(0, 0, 0), new Vector(7, 0, 0)));
	goal->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 50, 100), "Goal"));
	m_entities.push_back(goal);

	//	Create start entity.
	Entity* start = new Entity();
	start->addComponent(new PositionComponent(m_startPos));
	start->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 50, 100), "start"));
	start->addComponent(new GraphicsComponent(flagTexture, SDL2Help::InitRect(0, 314, 158, 314), SDL2Help::InitRect(0, 0, 50, 100)));
	start->addComponent(new AnimationComponent(new Vector(0, 0, 0), new Vector(7, 1, 0)));
	m_entities.push_back(start);

	//	Create block entity.
	Entity* block = new Entity();
	block->addComponent(new PositionComponent(Vector(850, 700)));
	block->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 55, 55), "Obstacle"));
	block->addComponent(new GraphicsComponent(blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 55, 55)));
	m_entities.push_back(block);


	//	Add all entities to relevant systems.
	for (Entity* entity : m_entities)
	{
		if (entity->getComponent("GRAPHICS") != nullptr)
		{
			m_graphics.addEntity(entity);
		}

		if (entity->getComponent("PHYSICS") != nullptr)
		{
			m_physics.addEntity(entity);
		}

		if (entity->getComponent("COLLISION") != nullptr)
		{
			m_collisions.addEntity(entity);
		}

		if (entity->getComponent("CONTROLLER") != nullptr)
		{
			m_controllers.addEntity(entity);
		}
	}		
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt, SDL_Event& e)
{
	m_controllers.update(dt, e);
	m_physics.update(dt);
	m_collisions.update(dt);
	m_graphics.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Autumn::render()
{
	m_graphics.render(m_renderer);
}
