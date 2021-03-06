#include "Screens/Levels/Summer.h"

/// <summary>
/// 
/// </summary>
Summer::Summer(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, Vector(0, 800), Vector(1400, 200))
{
	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Summer//Summer.png", m_renderer));

	spawnPlayers(1, false);
	spawnLevelObstacles();
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Summer::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Summer::render()
{
	m_entityManager.render();
}



/// <summary>
/// 
/// </summary>
void Summer::spawnLevelObstacles()
{
	m_entityManager.createPlatform(Vector(300, 750), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Summer//rock.png", m_renderer), { 0, 0, 200, 150 }, { 0, 0, 200, 150 });
	m_entityManager.createPlatform(Vector(800, 650), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Summer//parasol.png", m_renderer), { 0, 0, 150, 250 }, { 0, 0, 150, 250 });
	
	m_entityManager.createPlatform(Vector(1300, 300), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Summer//lifegaurd tower.png", m_renderer),{ 0, 0, 200, 600 }, { 0, 0, 200, 600 });	

	m_entityManager.createGoal(Vector(1300, 200), { 0, 0, 50, 100 });
}



/// <summary>
/// 
/// </summary>
void Summer::loadTextures()
{
	//	Red
	m_playerTextures["Red"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Summer//Lifeguard//Red_Lifeguard.png", m_renderer)));
	//	Blue
	m_playerTextures["Blue"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Summer//Lifeguard//Blue_Lifeguard.png", m_renderer)));
	//	Green
	m_playerTextures["Green"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Summer//Lifeguard//Green_Lifeguard.png", m_renderer)));
	//	Yellow
	m_playerTextures["Yellow"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({}, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Summer//Lifeguard//Yellow_Lifeguard.png", m_renderer)));
}
