#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Screen.h"
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/ControlSystem.h"
#include "ECS/Entities/Entity.h"

class Autumn : public Screen
{
public:
	Autumn(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt, SDL_Event& e) override;
	virtual void render() override;
private:
	GraphicsSystem m_graphics;
	PhysicsSystem m_physics;
	CollisionSystem m_collisions;
	ControlSytem m_controller;
	std::vector<Entity*> m_entities;
};
#endif // !AUTUMN_H
