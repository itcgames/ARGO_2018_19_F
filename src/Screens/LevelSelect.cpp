#include "Screens\LevelSelect.h"

/// <summary>
/// 
/// </summary>
LevelSelect::LevelSelect(ScreenManager* screenManager) :
	Screen(screenManager)
{
	m_screenID = "LevelSelect";
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void LevelSelect::update(double dt)
{
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void LevelSelect::render(SDL_Renderer * renderer)
{
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToSpring()
{
	m_screenManager->addScreen(new Spring(m_screenManager));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToSummer()
{
	m_screenManager->addScreen(new Summer(m_screenManager));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToAutumn()
{
	m_screenManager->addScreen(new Autumn(m_screenManager));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToWinter()
{
	m_screenManager->addScreen(new Winter(m_screenManager));
}
