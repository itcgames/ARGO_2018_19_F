#include "ECS/Systems/CharacterControlSystem.h"

/// <summary>
/// 
/// </summary>
CharacterControlSystem::CharacterControlSystem() : 
	m_state(new IdleState())
{
	
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void CharacterControlSystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");

		if (entity->getId() == "player" && physicsComponent != nullptr && controller != nullptr)
		{
			PlayerState* state = m_state->handleState(entity, controller->getCurrentState());
			m_state->update(dt, entity);
			if (state != nullptr)
			{
				delete(m_state);
				m_state = state;
				m_state->enter(entity);
			}
		}		
	}
}
