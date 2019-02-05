#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Screen.h"
#include "ECS/Systems/GraphicsSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Entities/Entity.h"

class Autumn : public Screen
{
public:
	Autumn(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:
	GraphicsSystem* m_graphics;
	PhysicsSystem* m_physics;
	Entity* m_player;
};
#endif // !AUTUMN_H
