#ifndef ITEM_COMPONENT_H
#define ITEM_COMPONENT_H

#include "ECS/Components/Component.h"

class ItemComponent : public Component
{
public:
	ItemComponent();

	bool isPlaced();
	void setPlaced(bool isPlaced);

private:
	bool m_isPlaced;
};
#endif // !ITEM_COMPONENT_H
