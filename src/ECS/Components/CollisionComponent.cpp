#include "ECS\Components\CollisionComponent.h"

/// <summary>
/// 
/// </summary>
CollisionComponent::CollisionComponent(SDL_Rect collider, std::string mainTag, std::string secondaryTag) :
	m_collider(collider),
	m_obstacleCursor(false),
	m_cursorActive(false),
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



/// <summary>
/// get Method for cursor state
/// </summary>
/// <returns></returns>
bool CollisionComponent::getCursorState()
{
	return m_cursorActive;
}



/// <summary>
/// Simple method to set the state of the onjetcs
/// </summary>
/// <param name="b"></param>
void CollisionComponent::setCursorState(bool b)
{
	m_cursorActive = b;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool CollisionComponent::getCollectedObj()
{
	return m_collectedObj;
}



/// <summary>
/// Simple method to set the state of the objects
/// </summary>
/// <param name="b"></param>
void CollisionComponent::setCollectedObj(bool b)
{
	m_collectedObj = b;
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
