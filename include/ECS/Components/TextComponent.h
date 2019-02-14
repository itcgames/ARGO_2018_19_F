#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "ECS/Components/Component.h"
#include "SDL.h"
#include "SDL_ttf.h"

class TextComponent : public Component
{
public:
	TextComponent(std::string text, int w, int h, SDL_Color colour);

	const char* getText();
	SDL_Color& getColour();
	SDL_Rect& getRect();

	void setColour(SDL_Color& colour);

private:
	char* m_text;
	SDL_Color m_colour;
	SDL_Rect m_destRect;
};
#endif // !TEXT_COMPONENT_H
