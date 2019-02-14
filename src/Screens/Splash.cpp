#include "Screens\Splash.h"

/// <summary>
/// 
/// </summary>
Splash::Splash(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer)
{
	m_screenID = "Splash";

	m_entities.push_back(EntityCreator::createLabel(Vector(800, 450), "ARGO", { 125,255,255 }, 400, 100));

	for (Entity* entity : m_entities)
	{
		if (entity->getComponent("TEXT") != nullptr || entity->getComponent("GRAPHICS") != nullptr)
		{
			m_ui.addEntity(entity);
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Splash::update(double dt)
{
	m_ui.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Splash::render()
{
	m_ui.render(m_renderer);
}
