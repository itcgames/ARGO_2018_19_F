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
	m_previousScreenID = "Menu";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Menu.png", renderer));
	m_entityManager.createImage({ 430, -100 }, SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//WoodenBack.png", m_renderer), { 0, 0, 700, 1100 });

	m_entityManager.createButton(0, true,  "Play",  Vector(775, 350), "Vs. A.I.", { 125, 255, 255 }, 400, 100);
	m_entityManager.createButton(1, false, "Lobby", Vector(775, 500), "Online",   { 125, 255, 255 }, 400, 100);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void ModeSelect::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
void ModeSelect::render()
{
	m_entityManager.render();
}
