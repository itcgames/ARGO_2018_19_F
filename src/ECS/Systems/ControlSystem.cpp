#include "ECS/Systems/ControlSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
/// <param name="e"></param>
void ControlSystem::update(double dt, SDL_Event e)
{	
	for (Entity* entity : m_entities)
	{
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");
			
		// NOTE: We have a controller with index ControllerIndex.
		bool Up = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
		bool Down = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		bool Left = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		bool Right = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		bool Start = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_START);
		bool Back = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_BACK);
		bool LeftShoulder = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		bool RightShoulder = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
		bool AButton = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_A);
		bool BButton = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_B);
		bool XButton = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_X);
		bool YButton = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_Y);

		int LeftStickX = SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_LEFTX);
		int LeftStickY = SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_LEFTY);
		int RightStickX = SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_RIGHTX);
		int RightStickY = SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_RIGHTY);
			
		if (AButton == true)
		{
			std::cout << "A button" << std::endl;
		}

		std::cout << "x value: "<< LeftStickX <<"  y value: "<< LeftStickY << std::endl;
	}
}