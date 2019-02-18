#include "Screens\Splash.h"

/// <summary>
/// 
/// </summary>
Splash::Splash(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer)
{
	m_screenID = "Splash";

	m_entityManager.createLabel(Vector(800, 450), "ARGO", { 125,255,255 }, 400, 100);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Splash::update(double dt)
{
	m_entityManager.getUIGraphicsSystem()->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Splash::render()
{
	m_entityManager.getUIGraphicsSystem()->render(m_renderer);
}
