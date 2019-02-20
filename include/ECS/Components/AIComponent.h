#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class AIComponent : public Component
{
public:
	AIComponent();

private:
	Vector m_nextMove;
};

#endif // !AI_COMPONENT_H
