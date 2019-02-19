#include "ECS/Systems/UIGraphicsSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void UIGraphicsSystem::update(double dt)
{
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void UIGraphicsSystem::render(SDL_Renderer * renderer)
{	
	for (Entity* entity : m_entities)
	{
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("GRAPHICS");
		TextComponent* textComponent = (TextComponent*)entity->getComponent("TEXT");
		UIComponent* uiComponent = (UIComponent*)entity->getComponent("UI");
		ControllerComponent* controllerComponent = (ControllerComponent*)entity->getComponent("CONTROLLER");

		if (uiComponent != nullptr)
		{
			if (uiComponent->isSelected())
			{
				m_selected = uiComponent->getOrder();
			}

			if (controllerComponent != nullptr)
			{
				ControllerState currentState = controllerComponent->getCurrentState();
				ControllerState previousState = controllerComponent->getPreviousState();

				if (currentState.leftStick.y > controllerComponent->DEAD_ZONE)
				{

				}

				if (currentState.leftStick.y < controllerComponent->DEAD_ZONE)
				{

				}
			}

			if (uiComponent->getOrder() == m_selected && uiComponent->isSelected() == false)
			{
				uiComponent->setSelected(true);
			}
		}

		if (positionComponent != nullptr)
		{
			if (graphicsComponent != nullptr)
			{
				SDL_Rect src = graphicsComponent->getSourceRect();
				SDL_Rect dest = graphicsComponent->getDestRect();
				SDL_Texture* texture = graphicsComponent->getTexture();

				dest.x = positionComponent->getPos().x - dest.w / 2;
				dest.y = positionComponent->getPos().y - dest.h / 2;

				SDL_RenderCopy(renderer, texture, &src, &dest);
			}

			if (textComponent != nullptr)
			{
				if (m_font == nullptr)
				{
					m_font = TTF_OpenFont(".//resources//SHOWG.TTF", 500);
				}

				SDL_Surface* surface = TTF_RenderText_Solid(m_font, textComponent->getText(), textComponent->getColour());
				SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);

				SDL_Rect dest = textComponent->getRect();
				dest.x = positionComponent->getPos().x - dest.w / 2;
				dest.y = positionComponent->getPos().y - dest.h / 2;

				SDL_RenderCopy(renderer, message, NULL, &dest);
				SDL_DestroyTexture(message);
				SDL_FreeSurface(surface);
			}

		}
	}
}
