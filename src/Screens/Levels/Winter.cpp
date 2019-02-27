#include "Screens/Levels/Winter.h"

/// <summary>
/// 
/// </summary>
Winter::Winter(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Level(screenManager, renderer, Vector(0, 400), Vector(1500, 200))
{
	m_screenID = "Play";
	m_previousScreenID = "ModeSelect";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Winter//Winter.png", m_renderer));
	
	spawnLevelObstacles();
	spawnPlayers(1, false);
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
	m_entityManager.createPlatform(Vector(-100, 500), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Winter//iceberg_1.png", m_renderer), {0, 0, 300, 600}, {0, 100, 300, 600});
	m_entityManager.createPlatform(Vector(1400, 200), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Winter//iceberg_1.png", m_renderer), { 0, 0, 300, 900 }, { 0, 100, 300, 900 });

	m_entityManager.createGoal(m_endPos, { 0, 0, 200, 100 }, SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Winter//Igloo.png", m_renderer), { 0, 0, 200, 100 });
}



/// <summary>
/// 
/// </summary>
void Winter::loadTextures()
{
	//	Red
	m_playerTextures["Red"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({0, 0, 597, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Santa Walk_Running Animations//Red_Santa_Walking.png", m_renderer)));
	m_playerTextures["Red"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({0, 0, 748, 931 },SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Run Animation//Red_Snowman_Walking.png", m_renderer)));
	//	Blue
	m_playerTextures["Blue"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 597, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Santa Walk_Running Animations//Blue_Santa_Walking.png", m_renderer)));
	m_playerTextures["Blue"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 748, 931 },SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Run Animation//Blue_Snowman_Walking.png", m_renderer)));
	//	Green
	m_playerTextures["Green"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 597, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Santa Walk_Running Animations//Green_Santa_Walking.png", m_renderer)));
	m_playerTextures["Green"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 748, 931 },SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Run Animation//Green_Snowman_Walking.png", m_renderer)));
	//	Yellow
	m_playerTextures["Yellow"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 597, 931 }, SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Santa//Santa Walk_Running Animations//Yellow_Santa_Walking.png", m_renderer)));
	m_playerTextures["Yellow"].push_back(std::make_pair<SDL_Rect, SDL_Texture*>({ 0, 0, 748, 931 },SDL2Help::LoadTexture(m_resourcesPath + "Characters//Winter//Snowman//Run Animation//Yellow_Snowman_Walking.png", m_renderer)));
}
