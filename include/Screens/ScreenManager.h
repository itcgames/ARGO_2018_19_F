#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
//	Standard.
#include <map>
//	Project.
#include "Screen.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	void update(double dt);
	void render(SDL_Renderer* renderer);

	void addScreen(Screen* screen);
	void goToScreen(std::string screenID);
	Screen* getCurrentScreen();

private:
	std::map<std::string, Screen*> m_screens;
	Screen* m_currentScreen;
};
#endif // !SCREEN_MANAGER_H
