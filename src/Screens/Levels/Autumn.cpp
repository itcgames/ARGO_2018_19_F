#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_startPos(100,800)
{
	m_screenID = "Play";

	SDL_Texture* backgroundTexture = SDL2Help::LoadTexture(m_resourcesPath + "AutumnBackground.png", m_renderer);
	SDL_Texture* playerTexture = SDL2Help::LoadTexture(m_resourcesPath + "test-sheet.png", m_renderer); // testing
	SDL_Texture* flagTexture = SDL2Help::LoadTexture(m_resourcesPath + "flags.png", m_renderer);
	SDL_Texture* blockTexture = SDL2Help::LoadTexture(m_resourcesPath + "woodBlock.png", m_renderer);
	SDL_Texture* deathTexture = SDL2Help::LoadTexture(m_resourcesPath + "tombstone.png", m_renderer);
	SDL_Texture* spikeTexture = SDL2Help::LoadTexture(m_resourcesPath + "spikes.png", m_renderer);
	SDL_Texture* pauseTexture = SDL2Help::LoadTexture(m_resourcesPath + "pause.png", m_renderer);

	//	Create background entity.
	m_entities.push_back(EntityCreator::createBackground(backgroundTexture, SDL2Help::InitRect(0, 0, 6703, 3762)));
	
	//	Create player entity.
	m_entities.push_back(EntityCreator::createPlayer(m_startPos, playerTexture, SDL2Help::InitRect(0, 0, 64, 64), SDL2Help::InitRect(0, 0, 64, 64), Vector(0, 0, 0), Vector(1, 0, 0), SDL2Help::InitRect(0, 0, 64, 64)));

	//  Create obstacle entity.
	m_entities.push_back(EntityCreator::createObstacle(Vector(800, 800), spikeTexture, SDL2Help::InitRect(0, 0, 142, 163), SDL2Help::InitRect(0, 0, 100, 100), SDL2Help::InitRect(0, 0, 100, 100)));
	
	//  Create Platform entity.
	m_entities.push_back(EntityCreator::createPlatform(Vector(300, 775), blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 100, 100), SDL2Help::InitRect(0, 0, 100, 100)));

	//	Create goal entity.
	m_entities.push_back(EntityCreator::createGoal(Vector(1400, 800), flagTexture, SDL2Help::InitRect(0, 0, 158, 314), SDL2Help::InitRect(0, 0, 50, 100), Vector(0, 1, 0), Vector(7, 1, 0), SDL2Help::InitRect(0, 0, 50, 100)));

	//	Create start entity.
	m_entities.push_back(EntityCreator::createStart(m_startPos, flagTexture, SDL2Help::InitRect(0, 314, 158, 314), SDL2Help::InitRect(0, 0, 50, 100), Vector(0, 0, 0), Vector(7, 1, 0), SDL2Help::InitRect(0, 0, 50, 100)));

	//create PauseBox Entity
	m_entities.push_back(EntityCreator::createSelectionBox(Vector(500, -1000), pauseTexture, SDL2Help::InitRect(0, 0, 1181, 1475), SDL2Help::InitRect(0, 0, 600, 800)));

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

		if (entity->getComponent("BOXPHYSICS") != nullptr)
		{
			m_boxPhysics.addEntity(entity);
		}
		if (entity->getComponent("COLLISION") != nullptr)
		{
			m_collisions.addEntity(entity);
		}

		if (entity->getComponent("CONTROLLER") != nullptr)
		{
			m_characterControl.addEntity(entity);
		}
	}		

	for (Entity* deathentity : m_deaths)
	{
		if (deathentity->getComponent("GRAPHICS") != nullptr)
		{
			m_graphics.addEntity(deathentity);
		}
	}
}




/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt, SDL_Event& e)

{
	m_boxPhysics.update(dt);
	m_characterControl.update(dt, e);
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
