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
	player->addComponent(new PositionComponent(Vector(200, 200, 0)));
	player->addComponent(new GraphicsComponent(texture, SDL2Help::InitRect(0, 0, 64, 64), SDL2Help::InitRect(0, 0, 32, 32)));
	player->addComponent(new PhysicsComponent());
	player->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 32, 32)));
	m_entities.push_back(player);

	//	Create goal entity.
	Entity* goal = new Entity();
	goal->addComponent(new PositionComponent(Vector(1500, 800)));
	goal->addComponent(new CollisionComponent(SDL2Help::InitRect(0, 0, 50, 50)));
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
	}		
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt, SDL_Event& e)
{
	m_physics.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Autumn::render()
{
	m_graphics.render(m_renderer);
}
