#include "ECS\Components\CollisionComponent.h"

/// <summary>
/// 
/// </summary>
CollisionComponent::CollisionComponent(SDL_Rect collider) :
	m_collider(collider),
	m_isColliding(false)
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
