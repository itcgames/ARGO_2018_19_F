#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

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

#endif // !PHYSICSSYSTEM_H
