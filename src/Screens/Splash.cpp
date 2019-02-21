#include "Screens\Splash.h"

/// <summary>
/// 
/// </summary>
Splash::Splash(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(m_screenManager, renderer)
{
	m_screenID = "Splash";

	m_entityManager.createLabel(Vector(800, 250), "Scary Claus Studio", { 125,255,255 }, 400, 100);
	m_entityManager.createImage({600, 350}, SDL2Help::LoadTexture(m_resourcesPath + "Logo.png", m_renderer), { 0, 0, 631, 716}, {0, 0, 400, 400});
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Splash::update(double dt)
{
	m_clock += dt;
	if (m_clock >= 3000)
	{
		m_screenManager->goToScreen("Title");
		m_clock = 0;
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Splash::render()
{
	m_entityManager.render();
}
