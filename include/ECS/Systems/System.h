#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "ECS/Entities/Entity.h"
#include "SDL.h"

class System
{
public:
	inline System() {}
	inline ~System() {}
	inline void addEntity(Entity * e) { m_entities.push_back(e); }
	inline void removeEntity(Entity * e) 
	{ 
		if (!m_entities.empty())
		{
			m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), e), m_entities.end());
		}
	}
	virtual void update(double dt) {}
	virtual void render(SDL_Renderer* renderer) {}

	std::vector<Entity*> m_entities;
protected:
};
#endif // !SYSTEM_H