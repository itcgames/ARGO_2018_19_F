#ifndef CURSOR_CONTROL_SYSTEM_H
#define CURSOR_CONTROL_SYSTEM_H

#include "ECS\Systems\System.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"

class CursorControlSystem :
	public System
{
public:
	CursorControlSystem();
	virtual ~CursorControlSystem();
	virtual void update(double dt) override;	
};
#endif // CURSOR_CONTROL_SYSTEM_H
