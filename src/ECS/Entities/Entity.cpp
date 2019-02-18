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
	m_components.try_emplace(c->getId(), c);
}



/// <summary>
/// remove a component from the current vector of components
/// </summary>
/// <param name="c">component pointer to be removed</param>
void Entity::removeComponent(Component * c)
{
	m_components.erase(c->getId());
}



/// <summary>
/// return a vector of component pointers
/// </summary>
/// <returns></returns>
std::map<std::string, Component*> Entity::getComponents()
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
	return m_components[componentId];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Entity::getId()
{
	return m_id;
}



/// <summary>
/// 
/// </summary>
/// <param name="id"></param>
void Entity::setId(std::string id)
{
	m_id = id;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::vector<Entity*> Entity::getLinkedEntities()
{
	return m_linkedEntities;
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void Entity::addLink(Entity * entity)
{
	m_linkedEntities.push_back(entity);
}



/// <summary>
/// 
/// </summary>
/// <param name="entity"></param>
void Entity::removeLink(Entity * entity)
{
	m_linkedEntities.erase(std::remove(m_linkedEntities.begin(), m_linkedEntities.end(), entity), m_linkedEntities.end());
}
