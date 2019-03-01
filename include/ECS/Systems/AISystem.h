#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/AIComponent.h"
#include "AI/Tile.h"
#include "AI/Grid.h"
#include "States/IdleState.h"

class AISystem : public System
{
public:
	AISystem();
	virtual void update(double dt);
	void processLevelEntities(CollisionSystem* collisionSystem);
	void render(SDL_Renderer* renderer);

private:
	Grid m_grid;
	PlayerState* m_state;
};
#endif // !AI_SYSTEM_H

