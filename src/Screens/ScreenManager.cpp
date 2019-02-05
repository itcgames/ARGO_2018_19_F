#include "Screens\ScreenManager.h"

/// <summary>
/// 
/// </summary>
ScreenManager::ScreenManager()
{
}



/// <summary>
/// 
/// </summary>
ScreenManager::~ScreenManager()
{
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void ScreenManager::update(double dt)
{
	m_currentScreen->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void ScreenManager::render(SDL_Renderer * renderer)
{
	m_currentScreen->render(renderer);
}



/// <summary>
/// 
/// </summary>
/// <param name="screen"></param>
void ScreenManager::addScreen(Screen * screen)
{
	m_screens[screen->getID()] = screen;
}



/// <summary>
/// 
/// </summary>
/// <param name="screenID"></param>
void ScreenManager::goToScreen(std::string screenID)
{
	m_currentScreen = m_screens[screenID];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Screen * ScreenManager::getCurrentScreen()
{
	return m_currentScreen;
}
