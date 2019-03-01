#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class AIComponent : public Component
{
public:
	AIComponent();

	void setGridLocation(int i, int j);
	Vector& getGridLocation();

	bool m_onPlatform;
	bool m_onGround;
	int m_jumpHeight;

private:

	Vector m_gridLocation;
};

#endif // !AI_COMPONENT_H
