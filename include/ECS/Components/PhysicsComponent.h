#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

//  Project.
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
	Vector& getMaxVelocity();
	Vector& getMaxJumpVelocity();
	Vector& getAcceleration();
	Vector& getFriction();
	bool getJumping();
	bool getGravity();

	void setVelocity(Vector& v);
	void setAcceleration(Vector& v);
	void setFriction(Vector& v);
	void setJumping(bool jump);

	void addAcceleration(float x, float y);

	void useGravity(bool g);

private:
	Vector m_velocity;
	Vector m_maxVelocity;
	Vector m_maxJumpVelocity;
	Vector m_acceleration;
	Vector m_friction;

	bool m_useGravity;
	bool m_isJumping;
};
#endif // !PHYSICS_COMPONENT_H
