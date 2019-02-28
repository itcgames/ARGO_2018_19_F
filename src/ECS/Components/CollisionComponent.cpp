#include "ECS\Components\CollisionComponent.h"

/// <summary>
/// 
/// </summary>
CollisionComponent::CollisionComponent(SDL_Rect collider, std::string mainTag, std::string secondaryTag) :
	m_collider(collider),
	m_mainTag(mainTag),
	m_secondaryTag(secondaryTag)
{
	m_id = "COLLISION";
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
SDL_Rect & CollisionComponent::getCollider()
{
	return m_collider;
}



/// <summary>
/// 
/// </summary>
/// <param name="collider"></param>
void CollisionComponent::setCollider(SDL_Rect & collider)
{
	m_collider = collider;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string CollisionComponent::getMainTag()
{
	return m_mainTag;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string CollisionComponent::getSecondaryTag()
{
	return m_secondaryTag;
}
