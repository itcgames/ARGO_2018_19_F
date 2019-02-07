#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer)
{
	m_screenID = "Play";

	SDL_Texture* texture = SDL2Help::LoadTexture(m_resourcesPath + "grid.png", m_renderer); // testing
	
	//	Create player entity.
	Entity* player = new Entity();
	player->addComponent(new PositionComponent(Vector(69, 200, 0)));
	player->addComponent(new GraphicsComponent(texture, SDL2Help::InitRect(0, 0, 85, 85), SDL2Help::InitRect(0, 0, 32, 32)));
	player->addComponent(new AnimationComponent(new Vector(0,0,0), new Vector(5,1,0)));
	player->addComponent(new PhysicsComponent());
	player->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 32, 32), "Player"));
	player->addComponent(new ControllerComponent());
	m_entities.push_back(player);

	// Level Obstacle Entity
	Entity* obstacle = new Entity();
	obstacle->addComponent(new PositionComponent(Vector(100, 600, 0)));
	obstacle->addComponent(new GraphicsComponent(texture, SDL2Help::InitRect(0, 85, 85, 85), SDL2Help::InitRect(0, 0, 100, 200)));
	obstacle->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 100, 200), "Obstacle"));
	m_entities.push_back(obstacle);

	//	Create goal entity.
	Entity* goal = new Entity();
	goal->addComponent(new PositionComponent(Vector(1600, 900)));
	goal->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 50, 50), "Obstacle"));
	m_entities.push_back(goal);

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
