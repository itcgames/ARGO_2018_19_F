#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

//  Project.
#include "ECS/Components/Component.h"
#include "SDL.h"

class GraphicsComponent : public Component 
{
public:
	GraphicsComponent(SDL_Texture * texture, SDL_Rect srcRect, SDL_Rect destRect, int layer = 0);

	SDL_Texture* getTexture();
	void setTexture(SDL_Texture * texture);

	SDL_Rect& getSourceRect();
	void setSourceRect(SDL_Rect rect);

	SDL_Rect& getDestRect();
	void setDestRect(SDL_Rect rect);

	int getLayer();

private:
	SDL_Texture* m_texture;
	SDL_Rect m_destRect;
	SDL_Rect m_srcRect;
	int m_layer;
};
#endif // !GRAPHICS_COMPONENT_H
