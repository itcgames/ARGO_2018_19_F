#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "SDL2_Helper/SDL2Helper.h"

class CollisionSystem : public System
{
public:
	virtual void update(double dt) override;

	void cursorUpdate(CollisionComponent *e1Collision, CollisionComponent *e2Collision, PositionComponent *e1Position, PositionComponent *e2Position);
	void playerUpdate(CollisionComponent *e1Collision, CollisionComponent *e2Collision, PositionComponent *e1Position, PositionComponent *e2Position);
private:
	std::string handleBoxCollision(Vector& p1, SDL_Rect& c1, Vector& p2, SDL_Rect& c2);
	//Audio * sound;
	Audio * sound = createAudio(".//resources//Sounds//spiketrap.wav", 0, SDL_MIX_MAXVOLUME / 2);
	bool m_grabbed = false;
};
#endif // !COLLISION_SYSTEM_H
