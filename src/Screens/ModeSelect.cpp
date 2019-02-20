#include "Screens\ModeSelect.h"

/// <summary>
/// 
/// </summary>
/// <param name="screenManager"></param>
/// <param name="renderer"></param>
ModeSelect::ModeSelect(ScreenManager * screenManager, SDL_Renderer * renderer) :
	Screen(screenManager, renderer),
	m_entityManager(screenManager, renderer)
{
	m_screenID = "ModeSelect";
	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//menubackground.png", renderer), { 0, 0, 1603, 909 });
	m_entityManager.createImage({ 430, -100 }, SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//WoodenBack.png", m_renderer), { 0, 0, 500, 700 }, { 0, 0, 700, 1100 });

	m_entityManager.getUIControlSystem()->initSystem();
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void ModeSelect::update(double dt)
{
	m_entityManager.getUIControlSystem()->update(dt);
}



/// <summary>
/// 
/// </summary>
void ModeSelect::render()
{
	m_entityManager.getGraphicsSystem()->render(m_renderer);
	m_entityManager.getUIGraphicsSystem()->render(m_renderer);
}
