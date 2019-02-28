#include "ECS/Systems/AISystem.h"

AISystem::AISystem()
{
	Vector screen = Vector(1600, 900);
	m_grid = Grid(screen, 50, 50);
}

void AISystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		PhysicsComponent* physics = (PhysicsComponent*)entity->getComponent("PHYSICS");
		Vector accel = physics->getAcceleration();
		//accel.x += .075;
		physics->setAcceleration(accel);
		m_grid.update(entity);
	}
}

void AISystem::processLevelEntities(CollisionSystem* collisionSystem)
{
	m_grid.processObstacles(collisionSystem);
}

void AISystem::render(SDL_Renderer * renderer)
{
	m_grid.render(renderer);
}
