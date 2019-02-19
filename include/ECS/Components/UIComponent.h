#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ECS/Components/Component.h"

class UIComponent : public Component
{
public:
	UIComponent(int order, bool selected);

	int getOrder();
	void setOrder(int order);

	bool isSelected();
	void setSelected(bool selected);

private:
	int m_order;
	bool m_selected;
};
#endif // !UI_COMPONENT_H
