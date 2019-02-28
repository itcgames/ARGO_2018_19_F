#ifndef AI_CURSOR_CONTROL_SYSTEM_H
#define AI_CURSOR_CONTROL_SYSTEM_H

#include "ECS\Systems\System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PlacedComponent.h"
#include "AI/Tile.h"
#include "AI/Grid.h"


class AICursorControlSystem :
	public System
{
public:
	AICursorControlSystem();
	~AICursorControlSystem();
	void update(double dt, bool picking);// override;

private:
	Grid m_grid;
	float x = 0;
	float y = 0;
	bool random = false;
	bool m_right = false;
};

#endif // AI_CURSOR_CONTROL_SYSTEM_