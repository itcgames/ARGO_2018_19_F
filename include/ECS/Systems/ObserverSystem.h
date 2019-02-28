#ifndef OBSERVER_SYSTEM_H
#define OBSERVER_SYSTEM_H


#include "ECS/Systems/System.h"
#include <string.h>
#include <SDL_mixer.h>

class ObserverSystem :
	public System
{
public:
	ObserverSystem();
	~ObserverSystem();

	void playMainMusic();
	void playMenuMusic();


private:
	Mix_Chunk * m_musicMenu;
	Mix_Chunk * m_musicGame;

	bool m_menu;
	bool m_game;
};

#endif // !OBSERVER_SYSTEM_H