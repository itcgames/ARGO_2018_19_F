#ifndef BOX_PHYSICS_COMPONENT_H
#define BOX_PHYSICS_COMPONENT_H

//  Project.
#include "ECS\Components\Component.h"
#include "Vector/Vector.h"

class BoxPhysicsComponent :
	public Component
{
public:
	BoxPhysicsComponent();
	virtual ~BoxPhysicsComponent();

	/// <summary>
	/// Getters and Setters
	/// </summary>
	Vector& getVelocity();
	void setVelocity(Vector& v);

private :
	Vector m_acceleration;
	Vector m_velocity;
};
#endif // !BOX_PHYSICS_COMPONENT_H
