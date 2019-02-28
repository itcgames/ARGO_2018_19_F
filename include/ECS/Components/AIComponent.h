#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class AIComponent : public Component
{
public:
	AIComponent();

	bool m_onPlatform;
	bool m_onGround;
	int m_jumpHeight;
	Vector m_nextMove;

private:
};

#endif // !AI_COMPONENT_H
