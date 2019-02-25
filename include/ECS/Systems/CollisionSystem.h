#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PlayerStateComponent.h"
#include "SDL2_Helper/SDL2Helper.h"
#include <SDL_mixer.h>

class CollisionSystem : public System
{
public:
	CollisionSystem();

	virtual void update(double dt) override;

private:
	std::string handleBoxCollision(Vector& p1, SDL_Rect& c1, Vector& p2, SDL_Rect& c2);
	
	int m_collectionCount;
	bool m_grabbed;
	bool m_platGrab;
	bool m_obGrab;
	bool m_springGrab;

	Mix_Chunk * m_spikeSound;
};
#endif // !COLLISION_SYSTEM_H
