#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_startPos(100, 800),
	m_entityManager(m_screenManager, renderer),
	m_startMusic(true),
	m_count(0)
{

	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	SDL_Texture* backgroundTexture  = SDL2Help::LoadTexture(m_resourcesPath + "AutumnBackground.png",	m_renderer);
	SDL_Texture* playerTexture  	= SDL2Help::LoadTexture(m_resourcesPath + "redGhost.png",			m_renderer); // testing
	SDL_Texture* player1Texture  	= SDL2Help::LoadTexture(m_resourcesPath + "santaYellow.png",		m_renderer); // testing
	SDL_Texture* player2Texture 	= SDL2Help::LoadTexture(m_resourcesPath + "PumpkinNormal.png",		m_renderer); // testing
	SDL_Texture* player3Texture 	= SDL2Help::LoadTexture(m_resourcesPath + "test-sheet.png",			m_renderer); // testing
	SDL_Texture* flagTexture 		= SDL2Help::LoadTexture(m_resourcesPath + "flags.png",				m_renderer);
	SDL_Texture* blockTexture 		= SDL2Help::LoadTexture(m_resourcesPath + "woodBlock.png",			m_renderer);
	SDL_Texture* deathTexture		= SDL2Help::LoadTexture(m_resourcesPath + "tombstone.png",			m_renderer);
	SDL_Texture* spikeTexture 		= SDL2Help::LoadTexture(m_resourcesPath + "spikes.png",				m_renderer);
	SDL_Texture* pauseTexture 		= SDL2Help::LoadTexture(m_resourcesPath + "pause.png",				m_renderer);
	SDL_Texture* cursorTexture		= SDL2Help::LoadTexture(m_resourcesPath + "cursor.png",				m_renderer);
	SDL_Texture* springBoardTexture = SDL2Help::LoadTexture(m_resourcesPath + "springBoard.png",		m_renderer);

	//	Create background entity.
	m_entityManager.createBackground(backgroundTexture, SDL2Help::InitRect(0, 0, 6703, 3762));

	//	Create player entities.
	m_entityManager.createPlayer(0, m_startPos, player3Texture, SDL2Help::InitRect(0, 0, 64, 64), SDL2Help::InitRect(0, 0, 64, 64), Vector(0, 0, 0), Vector(1, 0, 0), SDL2Help::InitRect(0, 0, 64, 64), true);	
	m_entityManager.createAI(m_startPos, player3Texture, SDL2Help::InitRect(0, 0, 64, 64), SDL2Help::InitRect(0, 0, 64, 64), Vector(0, 0, 0), Vector(1, 0, 0), SDL2Help::InitRect(0, 0, 64, 64));

	//Test Obstacle
	//m_entityManager.PlatMove(Vector(500, 500), blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 200, 200), SDL2Help::InitRect(0, 0, 100, 100));
	
	m_entityManager.createPlatform(Vector(500, 500), blockTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 50, 50), SDL2Help::InitRect(0, 0, 50, 50));
	m_entityManager.createObstacle(Vector(100, 500), spikeTexture, SDL2Help::InitRect(0, 0, 1599, 1594), SDL2Help::InitRect(0, 0, 100, 100), SDL2Help::InitRect(0, 0, 100, 100));

	//Create Spring entity.
	//m_entityManager.createSpring(Vector(500, 700), springBoardTexture, SDL2Help::InitRect(0, 0, 512, 512), SDL2Help::InitRect(0, 0, 50, 75), SDL2Help::InitRect(0, 0, 50, 75));

	//	Create goal entity.
	m_entityManager.createGoal(Vector(1400, 800), flagTexture, SDL2Help::InitRect(0, 0, 158, 314), SDL2Help::InitRect(0, 0, 50, 100), Vector(0, 0, 0), Vector(7, 0, 0), SDL2Help::InitRect(0, 0, 50, 100));

	//	Create start entity.
	m_entityManager.createStart(m_startPos, flagTexture, SDL2Help::InitRect(0, 314, 158, 314), SDL2Help::InitRect(0, 0, 50, 100), Vector(0, 1, 0), Vector(7, 1, 0), SDL2Help::InitRect(0, 0, 50, 100));

	//create PauseBox Entity
	m_entityManager.createSelectionBox(Vector(500, -1000), pauseTexture, SDL2Help::InitRect(0, 0, 1181, 1475), SDL2Help::InitRect(0, 0, 600, 800));

	//create Cursor Entity
	m_entityManager.createCursor(Vector(200, 200), cursorTexture, SDL2Help::InitRect(0, 0, 256, 256), SDL2Help::InitRect(0, 0, 50, 50), SDL2Help::InitRect(0, 0, 50, 50));

	// Create AI cursor
	m_entityManager.createAICursor(Vector(500, 200), cursorTexture, SDL2Help::InitRect(0, 0, 256, 256), SDL2Help::InitRect(0, 0, 50, 50), SDL2Help::InitRect(0, 0, 50, 50));

	m_entityManager.getAISystem()->processLevelEntities(m_entityManager.getCollisionSystem());


}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt, SDL_Event& e)

{
	//Mix_Quit();
	BoxPhysicsSystem* boxPhy = m_entityManager.getBoxPhysicsSystem();
	boxPhy->update(dt);
	if (!boxPhy->getPause())
	{
		m_entityManager.getCharacterControlSystem()->update(dt, e);
		m_count = 0;
	}

	if (boxPhy->getPause())
	{
		if (m_count == 0)
		{
			m_entityManager.getAISystem()->processLevelEntities(m_entityManager.getCollisionSystem());
			m_count++;
		}
		//m_entityMa
		m_entityManager.getCursorControlSystem()->update(dt);
		m_entityManager.getAICursorControlSystem()->update(dt, true);
	}

	

	m_entityManager.getAISystem()->update(dt);
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
	m_entityManager.getAISystem()->render(m_renderer);
}
