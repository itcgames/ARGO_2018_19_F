#include "ECS/Entities/Entity.h"

/// <summary>
/// Default Constructor
/// </summary>
Entity::Entity()
{

}



/// <summary>
/// Default Destructor
/// </summary>
Entity::~Entity()
{

}



/// <summary>
/// add a component to the entity's avector of components if it doesnt already exist within
/// </summary>
/// <param name="c">component pointer to be added</param>
void Entity::addComponent(Component * c)
{
	std::string componentId = c->getId();
	bool hasComponent = false;
	for (Component *component : m_components)
	{
		if (componentId == component->getId())
		{
			hasComponent = true;
			break;
		}
	}

	if (!hasComponent)
	{
		m_components.push_back(c);
	}
}



/// <summary>
/// remove a component from the current vector of components
/// </summary>
/// <param name="c">component pointer to be removed</param>
void Entity::removeComponent(Component * c)
{
	m_components.erase(std::remove(m_components.begin(), m_components.end(), c), m_components.end());
}



/// <summary>
/// return a vector of component pointers
/// </summary>
/// <returns></returns>
std::vector<Component*> Entity::getComponents()
{
	return m_components;
}



/// <summary>
/// get a specific component from the array of components by iterating through and matching the id
/// </summary>
/// <param name="componentId">string representing the component id</param>
/// <returns>pointer to component if it exists</returns>
Component * Entity::getComponent(std::string componentId)
{
	for (Component *component : m_components)
	{
		if (componentId == component->m_id)
		{
			return component;
		}
	}

	return nullptr;
}
