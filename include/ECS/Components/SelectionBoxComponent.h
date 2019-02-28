#ifndef SELECTION_BOX_COMPONENT_H
#define SELECTION_BOX_COMPONENT_H

//  Project.
#include "ECS/Components/Component.h"

class SelectionBoxComponent : public Component
{
public:
	SelectionBoxComponent(bool isVisible);
	~SelectionBoxComponent();

	bool isVisible();
	void setIsVisible(bool isVisible);

private :
	bool m_visible;
};
#endif // !SELECTION_BOX_COMPONENT_H
