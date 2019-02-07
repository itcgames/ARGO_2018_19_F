#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();

	/// <summary>
	/// Getters and Setters
	/// </summary>
	Vector& getVelocity();
	Vector& getAcceleration();
	Vector& getFriction();
	bool getGravity();

	void setVelocity(Vector& v);
	void setAcceleration(Vector& v);
	void setFriction(Vector& v);
	void useGravity(bool g);

private:
	Vector m_velocity;
	Vector m_acceleration;
	Vector m_friction;

	bool m_useGravity;
};
#endif // !PHYSICS_COMPONENT_H
