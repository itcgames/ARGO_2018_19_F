#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "ECS/Components/Component.h"
#include "../submodules/SDL2_Helper/SDL2Helper.h"

enum class ButtonStates
{
	Up,
	Pressed,
	Highlighted
};

struct Texture
{
	SDL_Texture* texture;
	SDL_Rect srcRect;
};

class UIComponent : public Component
{
public:
	UIComponent(int index, bool selected, std::string goTo, Texture normalTexture, Texture highlightedTexture, Texture pressedTexture);

	int getIndex();
	void setIndex(int index);

	bool isSelected();
	void setSelected(bool selected);

	void setState(ButtonStates state);

	Texture getTexture();

	std::string getGoTo();

private:
	//	The index of the button.
	int m_index;
	//	If the button is selected or not.
	bool m_selected;

	//	This is the texture that will be used outside the class.
	Texture m_texture;

	//	These textures refer to states of the UI element.
	Texture m_normalTexture;
	Texture m_highlightedTexture;
	Texture m_pressedTexture;

	std::string m_goTo;
};
#endif // !UI_COMPONENT_H
