#include "ECS/Components/GraphicsComponent.h"

/// <summary>
/// Default Constructor - Initialise the graphics component by passing a texture and the src dimensions
/// </summary>
/// <param name="texture">texture pointer arguement for the component to render</param>
/// <param name="srcRect">srcRect - location on the loaded resource to be rendered</param>
/// <param name="destRect">destRect - the location and size of the entity in the game world</param>
GraphicsComponent::GraphicsComponent(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	m_id = "GRAPHICS";
	m_texture = texture;

	m_srcRect = srcRect;
	m_destRect = destRect;
}



/// <summary>
/// return pointer to the source texture 
/// </summary>
/// <returns>SDL_Texture pointer</returns>
SDL_Texture* GraphicsComponent::getTexture()
{
	return m_texture;
}



/// <summary>
/// get the texture source rectangle - used for graphics system
/// </summary>
/// <returns>SDL_Rect </returns>
SDL_Rect GraphicsComponent::getSourceRect()
{
	return m_srcRect;
}



/// <summary>
/// get's the destination rectangle - utilised for updating sprite location
/// </summary>
/// <returns>SDL_Rect</returns>
SDL_Rect GraphicsComponent::getDestRect()
{
	return m_destRect;
}