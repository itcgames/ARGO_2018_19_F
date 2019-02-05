#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entities\Entity.h"

class System
{
public:
	System();
	~System();
	void addEntity(Entity * e);
	void removeEntity(Entity * e);
	virtual void update() = 0;
protected:
	std::vector<Entity*> m_entities;
};
#endif // !SYSTEM_H