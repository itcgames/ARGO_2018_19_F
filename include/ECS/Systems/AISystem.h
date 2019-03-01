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
	void generatePath();

private:
	Grid m_grid;
	PlayerState* m_state;

	int m_pairIndex;
	std::vector<std::pair<Vector, bool>> m_path;
};
#endif // !AI_SYSTEM_H

