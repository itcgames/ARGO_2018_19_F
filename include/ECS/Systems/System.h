#ifndef SYSTEM_H
#define SYSTEM_H

#include "ECS/Entities/Entity.h"

class System
{
public:
	inline System() {};
	inline ~System() {};
	inline void addEntity(Entity * e) { m_entities.push_back(e); };
	inline void removeEntity(Entity * e) 
	{ 
		if (!m_entities.empty())
		{
			m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), e), m_entities.end());
		}
	};
	virtual void update(double dt) = 0;
protected:
	std::vector<Entity*> m_entities;
};
#endif // !SYSTEM_H