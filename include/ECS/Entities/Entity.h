#ifndef ENTITY_H
#define ENTITY_H

#include "ECS/Components/Component.h"
#include <map>
#include <algorithm>

class Entity
{
public:
	Entity();
	~Entity();

	void addComponent(Component * c);
	void removeComponent(Component * c);
	std::map<std::string, Component*> getComponents();
	Component* getComponent(std::string componentId);

	std::string id;
protected:
	std::map<std::string, Component*> m_components;
};
#endif // !ENTITY_H