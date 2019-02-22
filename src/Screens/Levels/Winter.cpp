#include "Screens/Levels/Winter.h"

/// <summary>
/// 
/// </summary>
Winter::Winter(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, Vector(), Vector())
{
	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds/Winter.png", m_renderer), { 0, 0, 6708, 3805 });

	spawnPlayers(1, false);
	spawnLevelObstacles();
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Winter::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Winter::render()
{
	m_entityManager.render();
}



/// <summary>
/// 
/// </summary>
void Winter::spawnLevelObstacles()
{
	m_entityManager.createPlatform(Vector(0, 500), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, {0, 0, 200, 400}, {0, 0, 200, 400});
	m_entityManager.createPlatform(Vector(1400, 200), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0, 0, 200, 700 }, { 0, 0, 200, 700 });
}



/// <summary>
/// 
/// </summary>
void Winter::loadTextures()
{
	//	Red
	m_playerTextures["Red"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Red_Santa.png", m_renderer));
	m_playerTextures["Red"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Red_Snowman.png", m_renderer));
	//	Blue
	m_playerTextures["Blue"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Blue_Santa.png", m_renderer));
	m_playerTextures["Blue"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Blue_Snowman.png", m_renderer));
	//	Green
	m_playerTextures["Green"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Green_Santa.png", m_renderer));
	m_playerTextures["Green"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Green_Snowman.png", m_renderer));
	//	Yellow
	m_playerTextures["Yellow"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Yellow_Santa.png", m_renderer));
	m_playerTextures["Yellow"].push_back(SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Yellow_Snowman.png", m_renderer));
}
