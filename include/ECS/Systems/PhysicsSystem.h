#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/ControllerComponent.h"

class PhysicsSystem : public System
{
public:
	virtual void update(double dt) override;
	void keepOnScreen(Vector& postion, Vector& velocity, Vector& dimensions);

private:
	Vector m_gravity = Vector(0,.05,0);
};
#endif // !PHYSICS_SYSTEM_H
