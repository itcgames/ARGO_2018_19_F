#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class PositionComponent : public Component 
{
public:
	PositionComponent();
	PositionComponent(Vector &v);
	void setPos(Vector &v);
	Vector* getPos();

private:
	Vector* m_position;
};

#endif // !POSITIONCOMPONENT_H
