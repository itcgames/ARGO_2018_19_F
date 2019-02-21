#include "Screens\Credits.h"

/// <summary>
/// 
/// </summary>
Credits::Credits(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(screenManager, renderer)
{
	m_screenID = "Credits";
	
	m_entityManager.createBackground(SDL2Help::LoadTexture(m_resourcesPath + "Backgrounds//menubackground.png", renderer), { 0, 0, 1603, 909 });

	m_entityManager.createLabel(Vector(595, 120), "Game Created by:", { 0, 0, 0 },       420, 120);
	m_entityManager.createLabel(Vector(600, 125), "Game Created by:", { 255, 255, 255 }, 400, 100);
	m_entityManager.createLabel(Vector(695, 320), "D.J. O'Leary",     { 0, 0, 0 },		 420, 120);
	m_entityManager.createLabel(Vector(700, 325), "D.J. O'Leary",     { 255, 255, 255 }, 400, 100);
	m_entityManager.createLabel(Vector(795, 520), "Conor O'Toole",    { 0, 0, 0 },		 420, 120);
	m_entityManager.createLabel(Vector(800, 525), "Conor O'Toole",    { 255, 255, 255 }, 400, 100);
	m_entityManager.createLabel(Vector(895, 720), "John O'Grady",     { 0, 0, 0 },		 420, 120);
	m_entityManager.createLabel(Vector(900, 725), "John O'Grady",     { 255, 255, 255 }, 400, 100);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Credits::update(double dt)
{
	m_clock += dt;
	if (m_clock >= 3000)
	{
		exit(0);
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Credits::render()
{
	m_entityManager.getGraphicsSystem()->render(m_renderer);
	m_entityManager.getUIGraphicsSystem()->render(m_renderer);
}
