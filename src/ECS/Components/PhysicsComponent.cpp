#include "ECS/Components/PhysicsComponent.h"

/// <summary>
/// Default Constructor - initialise component variables
/// </summary>
PhysicsComponent::PhysicsComponent()
{
	m_id = "PHYSICS";
	m_velocity = Vector(0,0,0);
	m_maxVelocity = Vector(10, 10);
	m_acceleration = Vector(0,0,0);
	m_friction = Vector(.95,.99,0);
	m_useGravity = true;
}



/// <summary>
/// Getter - return a reference to component velocity
/// </summary>
/// <returns>velocity - vector pointer</returns>
Vector & PhysicsComponent::getVelocity()
{
	return m_velocity;
}


Vector & PhysicsComponent::getMaxVelocity()
{
	return m_maxVelocity;
}

/// <summary>
/// Getter - return a reference to component accleration
/// </summary>
/// <returns>acceleration - vector pointer</returns>
Vector & PhysicsComponent::getAcceleration()
{
	return m_acceleration;
}



/// <summary>
/// Getter - return a reference to component friction
/// </summary>
/// <returns>friction - vector pointer</returns>
Vector & PhysicsComponent::getFriction()
{
	return m_friction;
}



/// <summary>
/// Getter - return a component jumping
/// </summary>
/// <returns>jumping - boolean</returns>
bool PhysicsComponent::getJumping()
{
	return m_isJumping;
}



/// <summary>
/// Getter - return a reference to component gravity
/// </summary>
/// <returns>gravity - boolean</returns>
bool PhysicsComponent::getGravity()
{
	return m_useGravity;
}



/// <summary>
/// Setter - update component velocity value
/// </summary>
/// <param name="v">vector arguement</param>
void PhysicsComponent::setVelocity(Vector & v)
{
	m_velocity = v;
}



/// <summary>
/// Setter - update component acceleration value
/// </summary>
/// <param name="v">vector arguement</param>
void PhysicsComponent::setAcceleration(Vector & v)
{
	m_acceleration = v;
}



/// <summary>
/// Setter - update component friction value
/// </summary>
/// <param name="v">vector arguement</param>
void PhysicsComponent::setFriction(Vector & v)
{
	m_friction = v;
}



/// <summary>
/// Setter - update component jumping value
/// </summary>
/// <param name="v">boolean arguement</param>
void PhysicsComponent::setJumping(bool jump)
{
	m_isJumping = jump;
}



/// <summary>
/// Setter - update component gravity value
/// </summary>
/// <param name="v">boolean arguement</param>
void PhysicsComponent::useGravity(bool g)
{
	m_useGravity = g;
}

