#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_startPos(100,700)
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
	player->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 32, 32)));
	player->addComponent(new ControllerComponent());
	m_entities.push_back(player);

	//	Create goal entity.
	Entity* goal = new Entity();
	goal->addComponent(new PositionComponent(Vector(1000, 700)));
	goal->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 50,100)));
	goal->addComponent(new GraphicsComponent(flagTexture, SDL2Help::InitRect(0, 0, 158, 314), SDL2Help::InitRect(0, 0, 50, 100)));
	goal->addComponent(new AnimationComponent(new Vector(0, 0, 0), new Vector(7, 0, 0)));
	m_entities.push_back(goal);

	//	Create start entity.
	Entity* start = new Entity();
	start->addComponent(new PositionComponent(m_startPos));
	start->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 50, 100)));
	start->addComponent(new GraphicsComponent(flagTexture, SDL2Help::InitRect(0, 314, 158, 314), SDL2Help::InitRect(0, 0, 50, 100)));
	start->addComponent(new AnimationComponent(new Vector(0, 0, 0), new Vector(7, 1, 0)));
	m_entities.push_back(start);

	//	Create block entity.
	Entity* block = new Entity();
	block->addComponent(new PositionComponent(Vector(500, 700)));
	block->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 25, 25)));
	block->addComponent(new GraphicsComponent(blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 25, 25)));
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
	m_physics.update(dt);
	m_controllers.update(dt, e);
	m_graphics.update(dt);
	m_collisions.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Autumn::render()
{
	m_graphics.render(m_renderer);
}
