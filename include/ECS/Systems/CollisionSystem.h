#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "SDL2_Helper/SDL2Helper.h"
#include <SDL_mixer.h>

class CollisionSystem : public System
{
public:
	virtual void update(double dt) override;

	void cursorUpdate(CollisionComponent *e1Collision, CollisionComponent *e2Collision, PositionComponent *e1Position, PositionComponent *e2Position);
	void playerUpdate(CollisionComponent *e1Collision, CollisionComponent *e2Collision, PositionComponent *e1Position, PositionComponent *e2Position);
private:
	std::string handleBoxCollision(Vector& p1, SDL_Rect& c1, Vector& p2, SDL_Rect& c2);
	//Audio * sound;
	Mix_Chunk * m_spikeSound = Mix_LoadWAV(".//resources//Sounds//spiketrap.wav");
	int m_collectionCount = 0;
	bool m_grabbed = false;
	bool m_platGrab = false;
	bool m_obGrab = false;
	bool m_springGrab = false;
};
#endif // !COLLISION_SYSTEM_H
