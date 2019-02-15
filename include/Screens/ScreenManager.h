#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
//	Standard.
#include <map>
//	Project.
#include "SDL.h"
#include "Networking/TCP_Client.h"
#include "Networking/UDP_Client.h"

class Screen;

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();


	void update(double dt, SDL_Event &e);
	void render();

	void addScreen(Screen* screen);
	void goToScreen(std::string screenID);
	Screen* getCurrentScreen();
	Screen* getScreen(std::string screenID);

	std::pair<std::string, Client*> getClient();	

private:
	std::map<std::string, Screen*> m_screens;
	Screen* m_currentScreen;
	std::pair<std::string, Client*> m_client;
};
#endif // !SCREEN_MANAGER_H
