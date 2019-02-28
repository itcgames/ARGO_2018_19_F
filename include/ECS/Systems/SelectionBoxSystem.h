#ifndef BOX_PHYSICS_SYSTEM_H
#define BOX_PHYSICS_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/SelectionBoxComponent.h"

class SelectionBoxSystem : public System
{
public:
	virtual void update(double dt) override;
};
#endif // !BOX_PHYSICS_SYSTEM_H
