#include "ECS/Systems/GraphicsSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void GraphicsSystem::update(double dt)
{
	for (Entity* entity : m_entities)
	{
		AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");
		PhysicsComponent* physics = (PhysicsComponent*)entity->getComponent("PHYSICS");

		{
			if (animationComponent != nullptr)
			{
				double frameTime = animationComponent->getFrameTime();
				frameTime += dt;

				if (frameTime > 120)
				{
					Vector currentFrame = animationComponent->getCurrentFrame();
					Vector firstFrame = animationComponent->getFirstFrame();
					Vector lastFrame = animationComponent->getLastFrame();

					currentFrame.x++;
					if (currentFrame.x > lastFrame.x)
					{
						currentFrame.x = firstFrame.x;
					}

					animationComponent->setCurrentFrame(currentFrame);
					frameTime = 0;
				}

				animationComponent->setFrameTime(frameTime);
			}
		}
	}

}



/// <summary>
/// render all graphics components, updating any postion information for the sprites using the position component
/// </summary>
/// <param name="renderer"></param>
void GraphicsSystem::render(SDL_Renderer * renderer)
{
	std::vector<std::vector<Entity*>> sortedEntities;
	for (Entity* entity : m_entities)
	{
		GraphicsComponent* layer = (GraphicsComponent*)entity->getComponent("GRAPHICS");

	}

	for (Entity* entity : m_entities)
	{
		PositionComponent* positionComponent = (PositionComponent*)entity->getComponent("POSITION");
		GraphicsComponent* graphicsComponent = (GraphicsComponent*)entity->getComponent("GRAPHICS");
		AnimationComponent* animationComponent = (AnimationComponent*)entity->getComponent("ANIMATION");

		if (graphicsComponent != nullptr && positionComponent != nullptr)
		{
			SDL_Rect src = graphicsComponent->getSourceRect();
			SDL_Rect dest = graphicsComponent->getDestRect();
			SDL_Texture* texture = graphicsComponent->getTexture();



			dest.x = positionComponent->getPos().x;
			dest.y = positionComponent->getPos().y;

			if (animationComponent != nullptr)
			{
				Vector currentFrame = animationComponent->getCurrentFrame();
				src.x = currentFrame.x * src.w;
				src.y = currentFrame.y * src.h;

				animationComponent->m_centre = { src.x + src.w / 2, src.y + src.h / 2 };

				SDL_RenderCopyEx(renderer, texture, &src, &dest, animationComponent->m_angle, &animationComponent->m_centre, animationComponent->m_flip);
			}
			else
			{
				SDL_RenderCopy(renderer, texture, &src, &dest);
			}
		}
	}
}
