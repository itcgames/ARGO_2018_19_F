/// <summary>
/// System to control the update for the
/// Pause box
/// Score box
/// Selection box
/// </summary>
#ifndef BOX_PHYSICS_SYSTEM_H
#define BOX_PHYSICS_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/BoxPhysicsComponent.h"
#include "AI/Grid.h"

class BoxPhysicsSystem : public System
{
public:
	BoxPhysicsSystem();
	virtual void update(double dt) override;
	bool getPause();
private:
	bool m_paused;
	Grid * m_grid;
};

#endif // !BOX_PHYSICS_SYSTEM_H