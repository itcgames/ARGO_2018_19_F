#include "Screens\Menu.h"

/// <summary>
/// 
/// </summary>
Menu::Menu(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(m_screenManager, renderer)
{
	m_screenID = "Menu";	
	m_previousScreenID = "Title";

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Menu.png", renderer), {0, 0, 1603, 909});
	m_entityManager.createImage({ 430, -100 }, SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//WoodenBack.png", m_renderer), {0, 0, 500, 700}, { 0, 0, 700, 1100 });
	m_entityManager.createImage({ 432, 10 }, SDL2Help::LoadTexture(m_resourcesPath + "Hoppy Holidays Title//title.png", m_renderer), {0, 0, 1205, 401}, { 0, 0, 700, 200 });

	m_entityManager.createButton(0, true,  "ModeSelect",  Vector(775, 350), "Play",         { 125, 255, 255 }, 400, 100);
	m_entityManager.createButton(1, false, "LevelSelect", Vector(775, 500), "Level Select", { 125, 255, 255 }, 400, 100);
	m_entityManager.createButton(2, false, "Credits",     Vector(775, 650), "Quit",         { 125, 255, 255 }, 400, 100);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Menu::update(double dt)
{
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Menu::render()
{
	m_entityManager.render();
}
