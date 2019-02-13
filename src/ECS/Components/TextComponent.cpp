#include "ECS/Components/TextComponent.h"

TextComponent::TextComponent(std::string text, float w, float h, SDL_Color colour)
{
	m_id = "TEXT";
	m_text = text;
	m_destRect = { 0, 0, w, h };
	m_colour = colour;
}

std::string & TextComponent::getText()
{
	return m_text;
}

SDL_Color & TextComponent::getColour()
{
	return m_colour;
}

SDL_Rect & TextComponent::getRect()
{
	return m_destRect;
}
