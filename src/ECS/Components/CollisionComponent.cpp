#include "ECS\Components\CollisionComponent.h"

/// <summary>
/// 
/// </summary>
CollisionComponent::CollisionComponent(SDL_Rect collider, std::string tag) :
	m_collider(collider),
	m_isColliding(false),
	m_obstacleCursor(false)
{
	m_id = "COLLISION";
	m_tag = tag;
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
bool CollisionComponent::IsColliding()
{
	return m_isColliding;
}



/// <summary>
/// 
/// </summary>
/// <param name="isColliding"></param>
void CollisionComponent::setIsColliding(bool isColliding)
{
	m_isColliding = isColliding;
}

/// <summary>
///  Get method for collection
/// </summary>
bool CollisionComponent::getObstacleCursor()
{
	return m_obstacleCursor;
}

/// <summary>
/// Set method for collision response
/// </summary>
/// <param name="b"></param>
void CollisionComponent::setObstacleCursor(bool b)
{
	m_obstacleCursor = b;
}