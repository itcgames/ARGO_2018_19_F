#ifndef PLACED_COMPONENT_H
#define PLACED_COMPONENT_H

#include "ECS/Components/Component.h"

class PlacedComponent : public Component
{
public:
	PlacedComponent(bool placed = false);

	void setPlaced();
	bool getPlaced();

private:
	bool m_placed;
};
#endif // !PLACED_COMPONENT_H
