#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"

/// <summary>
/// 
/// </summary>
ScreenManager::ScreenManager()
{
	//	Initialise the client.
	m_client = new UDPClient();

	if (m_client->startWinsock())
	{
		if (m_client->createSocket())
		{

		}
	}

	observer = new ObserverSystem();
}



/// <summary>
/// 
/// </summary>
ScreenManager::~ScreenManager()
{
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void ScreenManager::update(double dt, SDL_Event &e)
{
	if (m_currentScreen->getID() == "Play")
	{
		m_currentScreen->update(dt, e);
		observer->playMainMusic();
		
	}
	else
	{
		m_currentScreen->update(dt);
		observer->playMenuMusic();
	}	
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void ScreenManager::render()
{
	m_currentScreen->render();
	Mix_Quit();
	//Mix_CloseAudio();
	//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 0, 2048);
}



/// <summary>
/// 
/// </summary>
/// <param name="screen"></param>
void ScreenManager::addScreen(Screen * screen)
{
	m_screens[screen->getID()] = screen;
}



/// <summary>
/// 
/// </summary>
/// <param name="screenID"></param>
void ScreenManager::goToScreen(std::string screenID)
{
	if (screenID == "Play")
	{
		Mix_FadeOutChannel(1, 1000);
		//Mix_Quit();
		//Mix_FadeInChannel(-1, -1, -1, 0);
	}
	m_currentScreen = m_screens[screenID];
}



/// <summary>
/// 
/// </summary>
void ScreenManager::backToPrevious()
{
	goToScreen(m_currentScreen->getPrevious());
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Screen * ScreenManager::getCurrentScreen()
{
	return m_currentScreen;
}



/// <summary>
/// 
/// </summary>
/// <param name="screenID"></param>
/// <returns></returns>
Screen * ScreenManager::getScreen(std::string screenID)
{
	return m_screens[screenID];
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
UDPClient* ScreenManager::getClient()
{
	return m_client;
}



/// <summary>
/// 
/// </summary>
/// <param name="client"></param>
void ScreenManager::setClient(UDPClient* client)
{
	m_client = client;
}
