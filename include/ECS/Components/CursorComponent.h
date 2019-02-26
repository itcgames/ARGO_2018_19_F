#ifndef CURSOR_COMPONENT_H
#define CURSOR_COMPONENT_H

#include "ECS/Components/Component.h"

class CursorComponent : public Component
{
public:
	CursorComponent();

	bool isActive();
	void setIsActive(bool active);
	void flipActive();

	bool isHoldingObject();
	void setIsHoldingObject(bool holdingObject);
	void flipHoldingObject();

private:
	bool m_active;
	bool m_holdingObject; 
};
#endif // !CURSOR_COMPONENT_H
