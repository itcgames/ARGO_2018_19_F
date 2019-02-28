#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

//  Project.
#include "ECS/Components/Component.h"
#include "SDL.h"

class GraphicsComponent : public Component 
{
public:
	GraphicsComponent(SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	SDL_Texture* getTexture();
	void setTexture(SDL_Texture * texture);

	SDL_Rect& getSourceRect();
	void setSourceRect(SDL_Rect rect);

	SDL_Rect& getDestRect();
	void setDestRect(SDL_Rect rect);

	double getAngle();
	void setAngle(double angle);

	SDL_Point* getCenter();
	void setCenter(SDL_Point* center);

	SDL_RendererFlip getFlip();
	void setFlip(SDL_RendererFlip flip);

private:
	SDL_Texture* m_texture;
	SDL_Rect m_destRect;
	SDL_Rect m_srcRect;
	double m_angle;
	SDL_Point* m_center;
	SDL_RendererFlip m_flip;
};
#endif // !GRAPHICS_COMPONENT_H
