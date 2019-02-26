#ifndef AI_CURSOR_CONTROL_SYSTEM_H
#define AI_CURSOR_CONTROL_SYSTEM_H

#include "ECS\Systems\System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "AI/Tile.h"
#include "AI/Grid.h"


class AICursorControlSystem :
	public System
{
public:
	AICursorControlSystem();
	~AICursorControlSystem();
	virtual void update(double dt, bool picking);// override;

private:
	Grid m_grid;
};

#endif // AI_CURSOR_CONTROL_SYSTEM_