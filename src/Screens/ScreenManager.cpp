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
	}
	else
	{
		m_currentScreen->update(dt);
	}	
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void ScreenManager::render()
{
	m_currentScreen->render();
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
