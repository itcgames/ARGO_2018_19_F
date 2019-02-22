#include "Screens\Title.h"

/// <summary>
/// 
/// </summary>
Title::Title(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(screenManager, renderer)
{
	m_screenID = "Title";
	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//menubackground.png", renderer), { 0, 0, 1603, 909 });
	m_entityManager.createImage({100, 100}, SDL2Help::LoadTexture(m_resourcesPath + "Hoppy Holidays Title//title.png", renderer), { 0, 0, 1205, 401 }, {0, 0, 1400, 400});
	m_entityManager.createButton(0, true, "Menu", {775, 650}, "Press A", { 125, 255, 255 }, 400, 100);

	m_entityManager.getUIControlSystem()->initSystem();;
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Title::update(double dt)
{
	m_entityManager.getUIControlSystem()->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Title::render()
{
	m_entityManager.getGraphicsSystem()->render(m_renderer);
	m_entityManager.getUIGraphicsSystem()->render(m_renderer);
}
