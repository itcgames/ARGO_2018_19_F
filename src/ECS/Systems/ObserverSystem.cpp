#include "ECS/Systems/ObserverSystem.h"



ObserverSystem::ObserverSystem() :
	m_game(true),
	m_menu(true)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "error: " << Mix_GetError() << std::endl;
	}

	m_musicMenu = Mix_LoadWAV(".//resources//Sounds//backgroundMenuMusic.wav");
	m_musicGame = Mix_LoadWAV("./resources//Sounds/background.wav");

}


ObserverSystem::~ObserverSystem()
{
}

void ObserverSystem::playMainMusic()
{
	if (m_game == true)
	{
		Mix_FadeOutChannel(2, 2000);
		Mix_FadeInChannel(1, m_musicGame, -1, 3000);
		//Mix_PlayChannel(1, m_musicGame, -1);
		m_game = false;
		m_menu = true;
	}
}

void ObserverSystem::playMenuMusic()
{
	if (m_menu == true)
	{
		Mix_PlayChannel(2, m_musicMenu, -1);
		m_menu = false;
		m_game = true;
	}
}