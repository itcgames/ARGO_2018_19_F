#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "SDL2_Helper/SDL2Helper.h"

class CollisionSystem : public System
{
public:
	virtual void update(double dt) override;
private:
	std::string handleBoxCollision(Vector& p1, SDL_Rect& c1, Vector& p2, SDL_Rect& c2);
};
#endif // !COLLISION_SYSTEM_H
