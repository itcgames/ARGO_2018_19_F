#ifndef UI_CONTROL_SYSTEM_H
#define UI_CONTROL_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/TextComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/ButtonComponent.h"
#include "ECS/Components/FuncButtonComponent.h"

#include "Screens/ScreenManager.h"

class UIControlSystem : public System
{
public:
	UIControlSystem(ScreenManager* screenManager);
	void initSystem();
	virtual void update(double dt) override;

private:
	void updateMinMax();
	void clampSelected();
	void updateTextures();

	int m_selected;	//	The number in the order that is selected.
	int m_max;
	int m_min;

	ControllerState m_currentState;
	ControllerState m_previousState;
	ScreenManager* m_screenManager;
};
#endif // !UI_CONTROL_SYSTEM_H
