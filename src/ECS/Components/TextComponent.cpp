#include "ECS/Components/TextComponent.h"

/// <summary>
/// 
/// </summary>
/// <param name="text"></param>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="colour"></param>
TextComponent::TextComponent(std::string text, int w, int h, SDL_Color colour)
{
	m_id = "TEXT";
	m_text = _strdup(text.c_str());
	m_destRect = { 0, 0, w, h };
	m_colour = colour;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
const char* TextComponent::getText()
{
	return m_text;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
SDL_Color & TextComponent::getColour()
{
	return m_colour;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
SDL_Rect & TextComponent::getRect()
{
	return m_destRect;
}



/// <summary>
/// 
/// </summary>
/// <param name="colour"></param>
void TextComponent::setColour(SDL_Color & colour)
{
	m_colour = colour;
}
