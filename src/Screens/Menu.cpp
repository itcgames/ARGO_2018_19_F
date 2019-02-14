#include "Screens\Menu.h"

/// <summary>
/// 
/// </summary>
Menu::Menu(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer)
{
	m_screenID = "Menu";
	SDL_Texture* blockTexture = SDL2Help::LoadTexture(m_resourcesPath + "woodBlock.png", m_renderer);

	m_entities.push_back(EntityCreator::createButton(Vector(800, 350), blockTexture, { 0,0,1599,1594 }, "Play", { 125, 255, 255 }, 400, 100));
	m_entities.push_back(EntityCreator::createButton(Vector(800, 500), blockTexture, { 0,0,1599,1594 }, "Settings", { 125, 255, 255 }, 400, 100));
	m_entities.push_back(EntityCreator::createButton(Vector(800, 650), blockTexture, { 0,0,1599,1594 }, "Quit", { 125, 255, 255 }, 400, 100));

	for (Entity* entity : m_entities)
	{
		if (entity->getComponent("TEXT") != nullptr || entity->getComponent("GRAPHICS"))
		{
			m_ui.addEntity(entity);
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Menu::update(double dt)
{
	m_ui.update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Menu::render()
{
	m_ui.render(m_renderer);
}
