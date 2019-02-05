#ifndef MENU_H
#define MENU_H
//	Project
#include "Screens/Screen.h"

class Menu : public Screen
{
public:
	Menu(ScreenManager* screenManager);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !MENU_H
