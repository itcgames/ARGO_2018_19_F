#include "ECS/Systems/ControlSystem.h"

void ControlSytem::update(double dt, SDL_Event e)
{	
	for (Entity* entity : m_entities)
	PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
	m_controller = new Controller();
	m_controller->update(e);


	//call component functions
}


