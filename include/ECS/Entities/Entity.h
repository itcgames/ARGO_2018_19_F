#ifndef ENTITY_H
#define ENTITY_H

#include "Components/Component.h"
#include <vector>
#include <algorithm>

class Entity
{
public:
	Entity();
	~Entity();

	void addComponent(Component * c);
	void removeComponent(Component * c);
	std::vector<Component*> getComponents();
	Component* getComponent(std::string componentId);

	std::string id;
protected:
	std::vector<Component*> m_components;
};
#endif // !ENTITY_H