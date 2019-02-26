#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, { 100, 700 }, {1300, 400}),
	m_startMusic(true)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "error: " << Mix_GetError() << std::endl;
	}

	m_music = Mix_LoadMUS(".//resources//Sounds//backgroundMenuMusic.mp3");
	m_effect = Mix_LoadWAV(".//resources//Sounds//background.wav");

	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Autumn.png", m_renderer));	

	spawnPlayers(1, false);
	spawnLevelObstacles();	
	m_entityManager.createSelectionBox();
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt)
{
	m_clock += dt;
	if (m_clock >= 10000 && m_gameInProgress == false)
	{
		//	Start the playing phase of the game.
		m_gameInProgress = true;
		SelectionBoxComponent* selectionBox = (SelectionBoxComponent*)m_entityManager.getEntityById("selection_box")->getComponent("SELECTION_BOX");
		selectionBox->setIsVisible(false);	

		std::vector<Entity*> players = m_entityManager.getEntitiesWithTag("player");
		for (Entity* player : players)
		{
			PlayerStateComponent* playerState = (PlayerStateComponent*)player->getComponent("PLAYER_STATE");
			PositionComponent* position = (PositionComponent*)player->getComponent("POSITION");

			//	Reset player state
			playerState->setAlive(true);
			playerState->setWon(false);

			//	Reset player position
			position->setPos(m_startPos);
		}
	}	

	m_entityManager.gameLoop(dt, m_gameInProgress, m_online);

	if (m_entityManager.getPlayerStateSystem()->getNumberOfPlayersStillPlaying() <= 0 && m_gameInProgress == true)
	{
		//	Start the placement phase of the game.
		m_gameInProgress = false;
		m_clock = 0;
		SelectionBoxComponent* selectionBox = (SelectionBoxComponent*)m_entityManager.getEntityById("selection_box")->getComponent("SELECTION_BOX");
		selectionBox->setIsVisible(true);	
	}

	if (m_startMusic)
	{
		//Mix_PlayChannel(2, m_effect, -1);
		m_startMusic = false;
	}
}



/// <summary>
/// 
/// </summary>
void Autumn::render()
{
	m_entityManager.render();
}



/// <summary>
/// Spawns all the default level obstacles and platforms.
/// </summary>
void Autumn::spawnLevelObstacles()
{	
	//	Load platforms the players can stand on.
	m_entityManager.createPlatform(Vector(1260, 500), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Pumpkin.png", m_renderer), { 0, 0, 80, 64 }, { 0, 0, 80, 64 });
	m_entityManager.createPlatform(Vector(1060, 700), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Pumpkin.png", m_renderer), { 0, 0, 80, 64 }, { 0, 0, 80, 64 });
	m_entityManager.createPlatform(Vector(570, 650),  SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Pumpkin.png", m_renderer), { 0, 0, 80, 64 }, { 0, 0, 80, 64 });

	//	Load obstacles.
	m_entityManager.createObstacle(Vector(0, 825), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Thorns.png", m_renderer), { 0, 0, 1600, 125 }, { 0, 0, 1600, 100 }, "Thorns");

	//	Load last platform.
	m_entityManager.createPlatform(Vector(0, 810), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Coffin.png", m_renderer), { 0, 0, 300, 100 }, { 0, 0, 300, 100 });	

	//	Load start and goal.
	m_entityManager.createStart(m_startPos, SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), {0, 0, 50, 100}, Vector(0,0), Vector(0,0), {0, 0, 50, 100});
	m_entityManager.createGoal(m_endPos, SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), {0, 0, 50, 100}, Vector(0, 0), Vector(0, 0), {0, 0, 50, 100});
}



/// <summary>
/// 
/// </summary>
void Autumn::loadTextures()
{
	//	Red
	m_playerTextures["Red"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Red_Ghost.png", m_renderer));
	m_playerTextures["Red"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Red_Pumpkin.png", m_renderer));
	//	Blue
	m_playerTextures["Blue"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Blue_Ghost.png", m_renderer));
	m_playerTextures["Blue"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Blue_Pumpkin.png", m_renderer));
	//	Green
	m_playerTextures["Green"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Green_Ghost.png", m_renderer));
	m_playerTextures["Green"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Green_Pumpkin.png", m_renderer));
	//	Yellow
	m_playerTextures["Yellow"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Yellow_Ghost.png", m_renderer));
	m_playerTextures["Yellow"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Yellow_Pumpkin.png", m_renderer));
}
