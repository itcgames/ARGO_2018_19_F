#include "ECS/Components/GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(SDL_Texture * texture, int srcX, int srcY, int width, int height)
{
	m_texture = texture;

	m_srcRect.x = srcX;
	m_srcRect.y = srcY;
	m_srcRect.w = width;
	m_srcRect.h = height;

	m_destRect.w = width;
	m_destRect.h = height;
}
