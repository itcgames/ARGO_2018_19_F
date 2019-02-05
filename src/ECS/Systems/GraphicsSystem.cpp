#include "ECS/Systems/GraphicsSystem.h"

/// <summary>
/// render all graphics components, updating any postion information for the sprites using the position component
/// </summary>
/// <param name="renderer"></param>
void GraphicsSystem::render(SDL_Renderer * renderer)
{
	for (Entity* entity : m_entities)
	{
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("GRAPHICS");

		std::cout << positionComponent->getPos().x << ", " << positionComponent->getPos().y << std::endl;

		if (graphicsComponent != nullptr && positionComponent != nullptr)
		{
			SDL_Rect src = graphicsComponent->getSourceRect();
			SDL_Rect dest = graphicsComponent->getDestRect();
			SDL_Texture* texture = graphicsComponent->getTexture();

			dest.x = positionComponent->getPos().x;
			dest.y = positionComponent->getPos().y;

			SDL_RenderCopy(renderer, texture, &src, &dest);
		}
	}
}
