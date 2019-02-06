#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H
//	Project
#include "ECS/Components/Component.h"
#include "SDL.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(SDL_Rect collider);

	SDL_Rect& getCollider();
	void setCollider(SDL_Rect& collider);

	bool IsColliding();
	void setIsColliding(bool isColliding);
private:
	SDL_Rect m_collider;
	bool m_isColliding;
};
#endif // !COLLISION_COMPONENT_H