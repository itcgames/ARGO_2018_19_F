#include "ECS/Components/BoxPhysicsComponent.h"



BoxPhysicsComponent::BoxPhysicsComponent() :
	m_velocity(0,1,0)

{
	m_id = "BoxPhysics";
}


BoxPhysicsComponent::~BoxPhysicsComponent()
{
}

Vector & BoxPhysicsComponent::getVelocity()
{
	return m_velocity;
}

void BoxPhysicsComponent::setVelocity(Vector &v)
{
	m_velocity = v;
}