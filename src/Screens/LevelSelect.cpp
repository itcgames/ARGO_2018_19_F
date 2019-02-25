#include "Screens\LevelSelect.h"

/// <summary>
/// 
/// </summary>
LevelSelect::LevelSelect(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(screenManager, renderer)
{
	m_screenID = "LevelSelect";
	m_previousScreenID = "Menu";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Menu.png", renderer), { 0, 0, 1603, 909 });
	m_entityManager.createImage(Vector(430, -100), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//WoodenBack.png", m_renderer), { 0, 0, 500, 700 }, { 0, 0, 700, 1100 });
	
	m_entityManager.createFunctionButton(Vector(640, 32),  0, true,  std::bind(&LevelSelect::setLevelToSpring, this), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Spring//Spring.png", m_renderer),	6705, 3793, 320, 180);
	m_entityManager.createFunctionButton(Vector(640, 244), 1, false, std::bind(&LevelSelect::setLevelToSummer, this), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Summer//Summer.png", m_renderer),	1613, 922,  320, 180);
	m_entityManager.createFunctionButton(Vector(640, 456), 2, false, std::bind(&LevelSelect::setLevelToAutumn, this), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Autumn//Autumn.png", m_renderer),	6708, 3805, 320, 180);
	m_entityManager.createFunctionButton(Vector(640, 668), 3, false, std::bind(&LevelSelect::setLevelToWinter, this), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Winter//Winter.png", m_renderer),	1596, 911,  320, 180);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void LevelSelect::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void LevelSelect::render()
{
	m_entityManager.render();
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToSpring()
{
	delete(m_screenManager->getScreen("Play"));
	m_screenManager->addScreen(new Spring(m_screenManager, m_renderer));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToSummer()
{
	delete(m_screenManager->getScreen("Play"));
	m_screenManager->addScreen(new Summer(m_screenManager, m_renderer));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToAutumn()
{
	delete(m_screenManager->getScreen("Play"));
	m_screenManager->addScreen(new Autumn(m_screenManager, m_renderer));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToWinter()
{
	delete(m_screenManager->getScreen("Play"));
	m_screenManager->addScreen(new Winter(m_screenManager, m_renderer));
}
