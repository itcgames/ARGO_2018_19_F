#ifndef CURSOR_CONTROL_SYSTEM_H
#define CURSOR_CONTROL_SYSTEM_H

#include "ECS\Systems\System.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PlacedComponent.h"

class CursorControlSystem : public System
{
public:
	virtual void update(double dt) override;	
};
#endif // CURSOR_CONTROL_SYSTEM_H
