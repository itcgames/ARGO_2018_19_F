#include "Screens\Settings.h"

/// <summary>
/// 
/// </summary>
Settings::Settings(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(screenManager, renderer)
{
	m_screenID = "Settings";
	m_previousScreenID = "Menu";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//menubackground.png", renderer), { 0, 0, 1603, 909 });
	m_entityManager.createImage(Vector(430, -100), SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//WoodenBack.png", m_renderer), { 0, 0, 500, 700 }, { 0, 0, 700, 1100 });

	m_entityManager.createButton(0, true,  "LevelSelect",     Vector(775, 350), "Level Select",     { 125, 255, 255 }, 400, 100);
	m_entityManager.createButton(1, false, "CharacterSelect", Vector(775, 500), "Character Select", { 125, 255, 255 }, 400, 100);

	m_entityManager.getUIControlSystem()->initSystem();
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Settings::update(double dt)
{
	m_entityManager.getUIControlSystem()->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Settings::render()
{
	m_entityManager.getGraphicsSystem()->render(m_renderer);
	m_entityManager.getUIGraphicsSystem()->render(m_renderer);
}
