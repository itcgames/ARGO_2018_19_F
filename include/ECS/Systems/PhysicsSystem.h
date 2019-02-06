#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/PositionComponent.h"

class PhysicsSystem : public System
{
public:
	virtual void update(double dt) override;

private:
	Vector m_gravity = Vector(0,.0098,0);
};
#endif // !PHYSICS_SYSTEM_H
