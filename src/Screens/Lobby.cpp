#include "Screens\Lobby.h"

/// <summary>
/// 
/// </summary>
/// <param name="screenManager"></param>
/// <param name="renderer"></param>
Lobby::Lobby(ScreenManager * screenManager, SDL_Renderer * renderer) :
	Screen(screenManager, renderer),
	m_entityManager(screenManager, renderer)
{	
	m_screenID = "Lobby";
	m_previousScreenID = "ModeSelect";	

	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//Menu.png", renderer));
	m_entityManager.createImage({ 430, -100 }, SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//WoodenBack.png", m_renderer), { 0, 0, 700, 1100 });

	m_entityManager.createButton(0, true,  "Play",  Vector(775, 750), "Start Game", { 125, 255, 255 }, 400, 100);
}



/// <summary>
/// Start winsock and then attempt to connect to the server.
/// </summary>
/// <param name="dt"></param>
void Lobby::update(double dt)
{	
	m_entityManager.update(dt);
}



/// <summary>
/// 
/// </summary>
void Lobby::render()
{
	m_entityManager.render();
}
