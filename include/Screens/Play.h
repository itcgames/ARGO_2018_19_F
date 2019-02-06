#ifndef PLAY_H
#define PLAY_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/ControlSystem.h"
#include "ECS/Entities/Entity.h"

class Play : public Screen
{
public:
	Play(SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:
	GraphicsSystem* m_graphics;
	PhysicsSystem* m_physics;
	Entity* m_player;
	ControlSytem* m_controller;
};
#endif // !PLAY_H
