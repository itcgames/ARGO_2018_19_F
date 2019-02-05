#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Components/Component.h"
#include "SDL.h"

class GraphicsComponent : public Component 
{
public:
	GraphicsComponent(SDL_Texture * texture, int srcX, int srcY, int width, int height);

private:
	SDL_Texture* m_texture;
	SDL_Rect m_destRect;
	SDL_Rect m_srcRect;

	int m_w;
	int m_h;
	int m_srcW;
	int m_srcH;
};

#endif // !GRAPHICSCOMPONENT_H
