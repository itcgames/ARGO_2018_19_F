#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

//  Project.
#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class PositionComponent : public Component 
{
public:
	PositionComponent();
	PositionComponent(Vector v);
	void setPos(Vector& v);
	Vector& getPos();

private:
	Vector* m_position;
};
#endif // !POSITION_COMPONENT_H
