#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/GraphicsComponent.h"

class PhysicsSystem : public System
{
public:
	virtual void update(double dt) override;
	void keepOnScreen(Vector& postion, Vector& velocity, SDL_Rect& dimensions, PhysicsComponent* physics);

private:
	const Vector GRAVITY = Vector(0,.05);
};
#endif // !PHYSICS_SYSTEM_H
