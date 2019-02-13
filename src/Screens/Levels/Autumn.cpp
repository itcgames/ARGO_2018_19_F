#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_startPos(100,800),
	m_entityManager(m_screenManager->getClient())
{
	m_screenID = "Play";

	SDL_Texture* backgroundTexture = SDL2Help::LoadTexture(m_resourcesPath + "AutumnBackground.png", m_renderer);
	SDL_Texture* playerTexture = SDL2Help::LoadTexture(m_resourcesPath + "grid.png", m_renderer); // testing
	SDL_Texture* flagTexture = SDL2Help::LoadTexture(m_resourcesPath + "flags.png", m_renderer);
	SDL_Texture* blockTexture = SDL2Help::LoadTexture(m_resourcesPath + "woodBlock.png", m_renderer);

	//	Create background entity.
	m_entityManager.createBackground(backgroundTexture, SDL2Help::InitRect(0, 0, 6703, 3762));
	
	//	Create player entities.
	m_entityManager.createPlayer(0, m_startPos, playerTexture, SDL2Help::InitRect(0, 85, 85, 85), SDL2Help::InitRect(0, 0, 32, 32), Vector(0, 0, 0), Vector(5, 1, 0), SDL2Help::InitRect(0, 0, 32, 32), true);
	m_entityManager.createPlayer(1, m_startPos, playerTexture, SDL2Help::InitRect(0, 85, 85, 85), SDL2Help::InitRect(0, 0, 32, 32), Vector(0, 0, 0), Vector(5, 1, 0), SDL2Help::InitRect(0, 0, 32, 32), false);

	// Create obstacle entities.
	m_entityManager.createObstacle(Vector(600, 700, 0), blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 100, 200), SDL2Help::InitRect(0, 0, 100, 200));
	m_entityManager.createObstacle(Vector(850, 700), blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 55, 55), SDL2Help::InitRect(0, 0, 55, 55));

	//	Create goal entity.
	m_entityManager.createGoal(Vector(1400, 800), flagTexture, SDL2Help::InitRect(0, 0, 158, 314), SDL2Help::InitRect(0, 0, 50, 100), Vector(0, 0, 0), Vector(7, 0, 0), SDL2Help::InitRect(0, 0, 50, 100));

	//	Create start entity.
	m_entityManager.createStart(m_startPos, flagTexture, SDL2Help::InitRect(0, 314, 158, 314), SDL2Help::InitRect(0, 0, 50, 100), Vector(0, 0, 0), Vector(7, 1, 0), SDL2Help::InitRect(0, 0, 50, 100));	
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt, SDL_Event& e)
{
	m_entityManager.getCharacterControlSystem()->update(dt, e);
	m_entityManager.getPhysicsSystem()->update(dt);
	m_entityManager.getCollisionSystem()->update(dt);
	m_entityManager.getGraphicsSystem()->update(dt);
	m_entityManager.getNetworkSystem()->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Autumn::render()
{
	m_entityManager.getGraphicsSystem()->render(m_renderer);
}
