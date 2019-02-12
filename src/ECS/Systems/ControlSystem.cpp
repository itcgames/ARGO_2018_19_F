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
		
			PhysicsComponent* physicsComponent = (PhysicsComponent*)entity->getComponent("PHYSICS");
			ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");
			GraphicsComponent* graphics = (GraphicsComponent*)entity->getComponent("GRAPHICS");
			PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");
			CollisionComponent* collision = (CollisionComponent*)entity->getComponent("COLLISION");

			std::map<std::string, bool> m_buttons;
			//  D-pad.
			m_buttons["up"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
			m_buttons["down"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
			m_buttons["left"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
			m_buttons["right"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
			//  Centre buttons.
			m_buttons["start"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_START);
			m_buttons["back"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_BACK);
			//  Shoulder buttons.
			m_buttons["leftShoulder"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
			m_buttons["rightShoulder"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
			//  Face buttons.
			m_buttons["a"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_A);
			m_buttons["b"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_B);
			m_buttons["x"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_X);
			m_buttons["y"] = SDL_GameControllerGetButton(controller->m_controller, SDL_CONTROLLER_BUTTON_Y);
			//  Left stick.
			Vector leftStick = Vector(SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_LEFTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_LEFTY) / MAX_STICK_VALUE);
			//  Right stick.
			Vector rightStick = Vector(SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_RIGHTX) / MAX_STICK_VALUE, SDL_GameControllerGetAxis(controller->m_controller, SDL_CONTROLLER_AXIS_RIGHTY) / MAX_STICK_VALUE);
			//  Handle inputs.
			Vector acceleration;
			
			if (controller->m_paused == false)
			{

				if (m_buttons["a"] && !physicsComponent->getJumping())
				{
					physicsComponent->setJumping(true);
					acceleration.y -= 1.5;
				}

				if (leftStick.x > controller->DEAD_ZONE && physicsComponent->getVelocity().x <= physicsComponent->getMaxVelocity().x)
				{
					if (physicsComponent->getJumping() == true)
					{
						acceleration.x += 0.025;
					}
					acceleration.x += 0.075;
				}
				else if (leftStick.x < -controller->DEAD_ZONE && physicsComponent->getVelocity().x >= -physicsComponent->getMaxVelocity().x)
				{
					if (physicsComponent->getJumping() == true)
					{
						acceleration.x -= 0.025;
					}
					acceleration.x -= 0.075;
				}

				if (m_buttons["b"] && !physicsComponent->getJumping())
				{
					graphics->setDestRect(10);
					SDL_Rect rect = { collision->getCollider().x, collision->getCollider().y, collision->getCollider().w, 10 };
					collision->setCollider(rect);
					Vector v = { position->getPos().x, position->getPos().y + 22 };
					position->setPos(v);
				}
				else
				{
					graphics->setDestRect(32);
					SDL_Rect rect = { collision->getCollider().x, collision->getCollider().y, collision->getCollider().w, 32 };
					collision->setCollider(rect);
				}

				physicsComponent->setAcceleration(acceleration);
				

				if (m_buttons["start"])
				{
					std::cout << "pause " + controller->m_paused << std::endl;
					controller->m_paused = true;
				}
				
			}

	}
}


