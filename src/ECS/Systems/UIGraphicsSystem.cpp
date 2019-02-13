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

		if (positionComponent != nullptr)
		{
			SDL_Rect src = graphicsComponent->getSourceRect();
			SDL_Rect dest = graphicsComponent->getDestRect();
			SDL_Texture* texture = graphicsComponent->getTexture();

			dest.x = positionComponent->getPos().x;
			dest.y = positionComponent->getPos().y;

			SDL_RenderCopy(renderer, texture, &src, &dest);

			if (textComponent != nullptr)
			{
				const char* text = textComponent->getText().c_str();
				SDL_Surface* surface = TTF_RenderText_Solid(m_font, text, textComponent->getColour());
				SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
				SDL_RenderCopy(renderer, message, &src, &dest);
			}
		}
	}
}
