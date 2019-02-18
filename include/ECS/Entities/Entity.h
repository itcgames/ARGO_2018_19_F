#ifndef ENTITY_H
#define ENTITY_H

#include "ECS/Components/Component.h"
#include <map>
#include <vector>
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
	
	std::string getId();
	void setId(std::string id);

	std::vector<Entity*> getLinkedEntities();
	void addLink(Entity* entity);
	void removeLink(Entity* entity);

protected:
	std::string m_id;
	std::map<std::string, Component*> m_components;
	std::vector<Entity*> m_linkedEntities;
};
#endif // !ENTITY_H