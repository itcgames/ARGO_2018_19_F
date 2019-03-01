#ifndef OBJECT_PLACED_SYSTEM_H
#define OBJECT_PLACED_SYSTEM_H


#include "ECS\Systems\System.h"
#include "ECS/Components/PlacedComponent.h"
class ObjectPlacedSystem :
	public System
{
public:
	ObjectPlacedSystem();
	~ObjectPlacedSystem();
	void update();
	int getNumberOfObjectsPlaced();

private:
	int m_placed;
};

#endif // !OBJECT_PLACED_SYSTEM_H