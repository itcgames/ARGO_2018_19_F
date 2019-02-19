#include "Screens\Menu.h"

/// <summary>
/// 
/// </summary>
Menu::Menu(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer)
{
	m_screenID = "Menu";
	SDL_Texture* blockTexture = SDL2Help::LoadTexture(m_resourcesPath + "woodBlock.png", m_renderer);

	//m_entityManager.createButton(1, true, Vector(800, 350), blockTexture, { 0,0,1599,1594 }, "Play", { 125, 255, 255 }, 400, 100);
	//m_entityManager.createButton(2, false, Vector(800, 500), blockTexture, { 0,0,1599,1594 }, "Settings", { 125, 255, 255 }, 400, 100);
	//m_entityManager.createButton(3, false, Vector(800, 650), blockTexture, { 0,0,1599,1594 }, "Quit", { 125, 255, 255 }, 400, 100);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Menu::update(double dt)
{
	m_entityManager.getUIGraphicsSystem()->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Menu::render()
{
	m_entityManager.getUIGraphicsSystem()->render(m_renderer);
}
