#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"

class CollisionSystem : public System
{
public:
	virtual void update(double dt) override;
private:

};
#endif // !COLLISION_SYSTEM_H
