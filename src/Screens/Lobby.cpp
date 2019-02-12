#include "Screens\Lobby.h"

/// <summary>
/// 
/// </summary>
/// <param name="screenManager"></param>
/// <param name="renderer"></param>
Lobby::Lobby(ScreenManager * screenManager, SDL_Renderer * renderer) :
	Screen(screenManager, renderer)
{	
	m_screenID = "Lobby";
	m_connected = false;
	Client* client = m_screenManager->getClient();
	if (client->startWinSock())
	{
		if (client->createSocket())
		{
			
		}
	}
}



/// <summary>
/// Start winsock and then attempt to connect to the server.
/// </summary>
/// <param name="dt"></param>
void Lobby::update(double dt)
{
	if (!m_connected)
	{
		connectToServer();
	}

	m_screenManager->goToScreen("Play");
}



/// <summary>
/// 
/// </summary>
void Lobby::render()
{
}



/// <summary>
/// 
/// </summary>
void Lobby::connectToServer()
{
	Client* client = m_screenManager->getClient();
	m_connected = client->connectToServer();
}
