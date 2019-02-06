#include "Screens\LevelSelect.h"

/// <summary>
/// 
/// </summary>
LevelSelect::LevelSelect(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer)
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
void LevelSelect::render()
{
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToSpring()
{
	m_screenManager->addScreen(new Spring(m_screenManager, m_renderer));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToSummer()
{
	m_screenManager->addScreen(new Summer(m_screenManager, m_renderer));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToAutumn()
{
	m_screenManager->addScreen(new Autumn(m_screenManager, m_renderer));
}



/// <summary>
/// 
/// </summary>
void LevelSelect::setLevelToWinter()
{
	m_screenManager->addScreen(new Winter(m_screenManager, m_renderer));
}
