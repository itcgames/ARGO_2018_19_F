#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H
//	Standard.
#include <map>
//	Project.
#include "SDL.h"
#include "Networking/TCP_Client.h"
#include "Networking/UDP_Client.h"
#include <SDL_mixer.h>
#include "ECS/Systems/ObserverSystem.h"

class Screen;

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();


	void update(double dt);
	void render();

	void addScreen(Screen* screen);
	void goToScreen(std::string screenID);
	void backToPrevious();
	Screen* getCurrentScreen();
	Screen* getScreen(std::string screenID);

	UDPClient* getClient();
	void setClient(UDPClient* client);

private:
	std::map<std::string, Screen*> m_screens;
	Screen* m_currentScreen;
	UDPClient* m_client;

	ObserverSystem *observer;
};
#endif // !SCREEN_MANAGER_H
