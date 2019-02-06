#include "Screens\Play.h"

/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
Play::Play(SDL_Renderer *renderer)
{
	SDL_Texture* texture = SDL2Help::LoadTexture(m_resourcesPath + "grid.png", renderer); // testing
	m_player = new Entity();
	m_graphics = new GraphicsSystem();
	m_physics = new PhysicsSystem();
	m_controller = new ControlSytem();

	m_player->addComponent(new PositionComponent(Vector(200, 200, 0)));
	m_player->addComponent(new GraphicsComponent(texture, SDL2Help::InitRect(0, 0, 64, 64), SDL2Help::InitRect(0, 0, 32, 32)));
	m_player->addComponent(new PhysicsComponent());

	m_graphics->addEntity(m_player);
	m_physics->addEntity(m_player);
	m_screenID = "Play";
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Play::update(double dt)
{
	m_physics->update(dt);
	m_controller->update(dt);
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Play::render(SDL_Renderer * renderer)
{
	m_graphics->render(renderer);
}
