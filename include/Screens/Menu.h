#ifndef MENU_H
#define MENU_H
//	Project
#include "Screens/Screen.h"

class Menu : public Screen
{
public:
	Menu(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:

};
#endif // !MENU_H
