#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "ECS/Components/Component.h"
#include "SDL.h"

class GraphicsComponent : public Component 
{
public:
	GraphicsComponent(SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect);
	SDL_Texture* getTexture();
	SDL_Rect getSourceRect();
	SDL_Rect getDestRect();

private:
	SDL_Texture* m_texture;
	SDL_Rect m_destRect;
	SDL_Rect m_srcRect;
};
#endif // !GRAPHICSCOMPONENT_H
