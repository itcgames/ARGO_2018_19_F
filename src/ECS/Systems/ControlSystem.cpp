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
		
        std::map<std::string, bool> m_buttons;
		bool isMoving = false;

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

        Vector acceleration = physicsComponent->getAcceleration();
		Vector velocity = physicsComponent->getVelocity();

		system("CLS");
		PlayerState* state = m_state->handleInput(*entity, m_buttons, MAX_STICK_VALUE);
		m_state->update(*entity);
		if (state != nullptr)
		{
			delete(m_state);
			m_state = state;
		}

        if (m_buttons["a"] && !physicsComponent->getJumping())
        {
			physicsComponent->setJumping(true);
            acceleration.y -= 1.5;
        }

        if (leftStick.x > controller->DEAD_ZONE && velocity.x <= physicsComponent->getMaxVelocity().x)
        {
            acceleration.x += 0.075;
			isMoving = true;
        }
        else if (leftStick.x < -controller->DEAD_ZONE && velocity.x >= -physicsComponent->getMaxVelocity().x)
        {
            acceleration.x -= 0.075;
			isMoving = true;
        }

		if (acceleration.x < 0.055)
		{
			velocity.x = 0;
		}

        physicsComponent->setAcceleration(acceleration);
		physicsComponent->setVelocity(velocity);
	}
}
