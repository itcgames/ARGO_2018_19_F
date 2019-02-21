#include "Screens/Levels/Autumn.h"

/// <summary>
/// 
/// </summary>
Autumn::Autumn(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, { 100, 800 }, {})
{
	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds/Autumn.png", m_renderer), {0, 0, 6708, 3805});

	spawnPlayers(1, false);
	spawnLevelObstacles();
}




/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Autumn::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Autumn::render()
{
	m_entityManager.render();
}



/// <summary>
/// 
/// </summary>
void Autumn::spawnLevelObstacles()
{
	//	Load platforms the players can stand on.
	m_entityManager.createPlatform(Vector(1260, 500), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, {0,0, 80, 64},     { 0,0, 80, 64 });
	m_entityManager.createPlatform(Vector(1060, 700), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0,0, 80, 64 },   { 0,0, 80, 64 });
	m_entityManager.createPlatform(Vector(570, 650),  SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0,0, 80, 64 },   { 0,0, 80, 64 });
	m_entityManager.createPlatform(Vector(0, 800),    SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0,0, 300, 100 }, { 0,0, 300, 100 });

	//	Load obstacles.
	m_entityManager.createObstacle(Vector(0, 832), SDL2Help::LoadTexture(m_resourcesPath + "Missing.png", m_renderer), { 0, 0, 200, 200 }, { 0,0, 1600, 64 }, { 0,0, 1600, 64 });
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
