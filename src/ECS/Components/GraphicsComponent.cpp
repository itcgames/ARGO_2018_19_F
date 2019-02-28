#include "ECS/Components/GraphicsComponent.h"

/// <summary>
/// Default Constructor - Initialise the graphics component by passing a texture and the src dimensions
/// </summary>
/// <param name="texture">texture pointer arguement for the component to render</param>
/// <param name="srcRect">srcRect - location on the loaded resource to be rendered</param>
/// <param name="destRect">destRect - the location and size of the entity in the game world</param>
/// /// <param name="layer">layer - determines what textures are drawn on top</param>
GraphicsComponent::GraphicsComponent(SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, double angle, SDL_Point* center, SDL_RendererFlip flip) :
	m_texture(texture),
	m_srcRect(srcRect),
	m_destRect(destRect),
	m_angle(angle),
	m_center(center),
	m_flip(flip)
{
	m_id = "GRAPHICS";
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
/// 
/// </summary>
/// <param name="texture"></param>
void GraphicsComponent::setTexture(SDL_Texture* texture)
{
	m_texture = texture;
}



/// <summary>
/// get the texture source rectangle - used for graphics system
/// </summary>
/// <returns>SDL_Rect </returns>
SDL_Rect& GraphicsComponent::getSourceRect()
{
	return m_srcRect;
}



/// <summary>
/// 
/// </summary>
/// <param name="height"></param>
void GraphicsComponent::setSourceRect(SDL_Rect rect)
{
	m_srcRect = rect;
}



/// <summary>
/// get's the destination rectangle - utilised for updating sprite location
/// </summary>
/// <returns>SDL_Rect</returns>
SDL_Rect& GraphicsComponent::getDestRect()
{
	return m_destRect;
}



/// <summary>
/// 
/// </summary>
/// <param name="height"></param>
void GraphicsComponent::setDestRect(SDL_Rect rect)
{
	m_destRect = rect;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
double GraphicsComponent::getAngle()
{
	return m_angle;
}



/// <summary>
/// 
/// </summary>
/// <param name="angle"></param>
void GraphicsComponent::setAngle(double angle)
{
	m_angle = angle;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
SDL_Point * GraphicsComponent::getCenter()
{
	return m_center;
}



/// <summary>
/// 
/// </summary>
/// <param name="center"></param>
void GraphicsComponent::setCenter(SDL_Point * center)
{
	m_center = center;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
SDL_RendererFlip GraphicsComponent::getFlip()
{
	return m_flip;
}



/// <summary>
/// 
/// </summary>
/// <param name="flip"></param>
void GraphicsComponent::setFlip(SDL_RendererFlip flip)
{
	m_flip = flip;
}
