#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Screen.h"
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/CharacterControlSystem.h"
#include "ECS/Systems/NetworkSystem.h"
#include "ECS/Entities/EntityCreator.h"

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
	CharacterControlSystem m_characterControl;
	NetworkSystem m_network;
	std::vector<Entity*> m_entities;
	Vector m_startPos;
};
#endif // !AUTUMN_H
