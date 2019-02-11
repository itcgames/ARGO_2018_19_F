#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

#include "ECS/Components/Component.h"
#include "SDL.h"

class GraphicsComponent : public Component 
{
public:
	GraphicsComponent(SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, int layer = 0);

	SDL_Texture* getTexture();
	SDL_Rect getSourceRect();
	SDL_Rect getDestRect();
	void setDestRect(int height);
	void setSourceRect(int height);
	int getLayer();


private:
	SDL_Texture* m_texture;
	SDL_Rect m_destRect;
	SDL_Rect m_srcRect;
	int m_layer;
};
#endif // !GRAPHICS_COMPONENT_H
