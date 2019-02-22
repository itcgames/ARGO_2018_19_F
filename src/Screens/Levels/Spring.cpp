#include "Screens/Levels/Spring.h"

/// <summary>
/// 
/// </summary>
Spring::Spring(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, Vector(0,700), Vector(0, 300))
{
	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds/Spring.png", m_renderer), { 0, 0, 6708, 3805 });

	spawnPlayers(1, false);
	spawnLevelObstacles();
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Spring::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Spring::render()
{
	m_entityManager.render();
}



/// <summary>
/// 
/// </summary>
void Spring::spawnLevelObstacles()
{
	//	Load platforms the players can stand on.
	m_entityManager.createPlatform(Vector(0, 800), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0,0, 80, 100 }, { 0,0, 80, 100 });
	m_entityManager.createPlatform(Vector(0, 400), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0,0, 800, 100 }, { 0,0, 800, 100 });
	m_entityManager.createKillBox(Vector(0, 850), { 0, 0, 1600, 50 });
}



/// <summary>
/// 
/// </summary>
void Spring::loadTextures()
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
