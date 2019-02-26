#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H
//	Project
#include "ECS/Components/Component.h"
#include "SDL.h"
#include <vector>

class CollisionComponent : public Component
{
public:
	CollisionComponent(SDL_Rect collider, std::string mainTag, std::string secondaryTag = "");

	SDL_Rect& getCollider();
	void setCollider(SDL_Rect& collider);

	std::string getMainTag();
	std::string getSecondaryTag();

private:
	SDL_Rect m_collider;

	std::string m_mainTag;
	std::string m_secondaryTag;
};
#endif // !COLLISION_COMPONENT_H
