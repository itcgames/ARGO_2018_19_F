#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, { 100, 700 }, {1300, 400})
{
	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Autumn.png", m_renderer));	

	spawnPlayers(1, false);
	spawnLevelObstacles();	
	m_entityManager.createSelectionBox();
	m_newObstacles = generateNewObstacles();

	for (int i = 0; i < 4; i++)
	{
		m_entityManager.createCursor(i);
	}

}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt)
{
	if (m_gameInProgress == false)
	{
		m_clock += dt;
	}

	if (m_clock >= 15000 && m_gameInProgress == false)
	{
		m_entityManager.getAISystem()->processLevelEntities(m_entityManager.getCollisionSystem());
		m_entityManager.getAISystem()->generatePath();
		//	Start the playing phase of the game.
		m_gameInProgress = true;
		m_generatedNewObstacles = false;
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
		//m_clock = 0;
		SelectionBoxComponent* selectionBox = (SelectionBoxComponent*)m_entityManager.getEntityById("selection_box")->getComponent("SELECTION_BOX");
		selectionBox->setIsVisible(true);	
		for (Entity* entity : m_entityManager.getObjectPlacedSystem()->m_entities)
		{
			m_entityManager.getObjectPlacedSystem()->removeEntity(entity);
		}

		if (m_generatedNewObstacles == false)
		{
			//m_entityManager.createSelectionBox();
			m_newObstacles = generateNewObstacles();
			for (int i = 0; i < 4; i++)
			{
				m_entityManager.createCursor(i);
			}
			
		}		

		bool allPlaced = true;
		for (Entity* entity : m_entityManager.getEntities())
		{
			if (entity->getId() == "platform" || entity->getId() == "obstacle")
			{
				PlacedComponent *placed = (PlacedComponent*)entity->getComponent("PLACED");
				if (placed->getPlaced() == false)
				{
					allPlaced = false;
					break;
				}
			}
		}
	
		if (allPlaced)
		{
			m_gameInProgress = true;
			std::vector<Entity*> cursors = m_entityManager.getEntitiesWithTag("cursor");
			for (Entity* cursor : cursors)
			{
				PlacedComponent *placed = (PlacedComponent*)cursor->getComponent("PLACED");
				if (placed->getPlaced() == true)
				{
					m_entityManager.removeEntity(cursor);
				}
			}

			for (Entity* obstacle : m_newObstacles)
			{
				PlacedComponent* placed = (PlacedComponent*)obstacle->getComponent("PLACED");
				placed->setPlaced(true);
			}
		}
	}

	SelectionBoxComponent* selectionBox = (SelectionBoxComponent*)m_entityManager.getEntityById("selection_box")->getComponent("SELECTION_BOX");

	if (m_clock > 5000)
	{
		selectionBox->setIsVisible(false);
		//m_entityManager.removeEntity(selectionBox);
	}

	if (m_clock >= 15000)
	{
		m_gameInProgress = true;
		std::vector<Entity*> cursors = m_entityManager.getEntitiesWithTag("cursor");
		for (Entity* cursor : cursors)
		{
			m_entityManager.removeEntity(cursor);
			//m_entityManager.removeEntity(m_entityManager.getSelectionBoxSystem());
		}

		for (Entity* obstacle : m_newObstacles)
		{
			PlacedComponent* placed = (PlacedComponent*)obstacle->getComponent("PLACED");
			placed->setPlaced(true);
			m_clock = 0;
		}
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
	m_entityManager.createGoal(m_endPos, { 0, 0, 50, 100 });
}



/// <summary>
/// 
/// </summary>
void Autumn::loadTextures()
{
	//	Red
	//m_playerTextures["Red"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Red_Ghost.png", m_renderer)));
	m_playerTextures["Red"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 558, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Run Animation//Red_Pumpkin_Walking.png", m_renderer)));
	//	Blue
	//m_playerTextures["Blue"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Blue_Ghost.png", m_renderer)));
	m_playerTextures["Blue"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 558, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Run Animation//Blue_Pumpkin_Walking.png", m_renderer)));
	//	Green
	//m_playerTextures["Green"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Green_Ghost.png", m_renderer)));
	m_playerTextures["Green"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 558, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Run Animation//Green_Pumpkin_Walking.png", m_renderer)));
	//	Yellow
	//m_playerTextures["Yellow"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Ghost//Yellow_Ghost.png", m_renderer)));
	m_playerTextures["Yellow"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 558, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Autumn//Pumpkin//Run Animation//Yellow_Pumpkin_Walking.png", m_renderer)));
}
