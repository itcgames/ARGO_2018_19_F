#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"

/// <summary>
/// 
/// </summary>
ScreenManager::ScreenManager()
{
	while (m_client.second == nullptr)
	{
		std::cout << "What protocol do you wish to use?" << std::endl;
		std::string input;
		std::cin >> input;

		if (input == "TCP" || input == "tcp" || input == "Tcp")
		{
			m_client.first = "TCP";
			m_client.second = new TCPClient();
		}
		else if (input == "UDP" || input == "udp" || input == "Udp")
		{
			m_client.first = "UDP";
			m_client.second = new UDPClient();
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
std::pair<std::string, Client*> ScreenManager::getClient()
{
	return m_client;
}
