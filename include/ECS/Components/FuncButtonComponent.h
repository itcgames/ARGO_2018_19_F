#ifndef FUNC_BUTTON_COMPONENT_H
#define FUNC_BUTTON_COMPONENT_H

#include "Component.h"
#include "SDL.h"
#include <functional>

enum class FuncButtonStates
{
	Selected,
	NotSelected
};

class FuncButtonComponent : public Component
{
public:
	FuncButtonComponent(int index, bool selected, std::function<void()> function, SDL_Rect defaultRect);

	int getIndex();
	void setIndex(int index);

	bool isSelected();
	void setSelected(bool selected);

	void callFunction();

	void setButtonState(FuncButtonStates state);
	SDL_Rect getDestRect();

private:
	//	The index of the button.
	int m_index;
	//	If the button is selected or not.
	bool m_selected;
	
	SDL_Rect m_destRect;
	SDL_Rect m_defaultRect;
	SDL_Rect m_scaledRect;

	//	Passed function.
	std::function<void()> m_function;
};
#endif // !FUNC_BUTTON_COMPONENT_H
