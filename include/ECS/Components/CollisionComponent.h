#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H
//	Project
#include "ECS/Components/Component.h"
#include "SDL.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(SDL_Rect collider, std::string tag);

	SDL_Rect& getCollider();
	void setCollider(SDL_Rect& collider);
	bool IsColliding();
	void setIsColliding(bool isColliding);
	bool getObstacleCursor();
	bool getCursorState();
	void setCursorState(bool b);
	void setObstacleCursor(bool b);
	bool getCollectedObj();
	void setCollectedObj(bool b);

	std::string m_tag;

private:
	SDL_Rect m_collider;
	bool m_isColliding;
	bool m_obstacleCursor;
	bool m_cursorActive;
	bool m_collectedObj;
};
#endif // !COLLISION_COMPONENT_H
