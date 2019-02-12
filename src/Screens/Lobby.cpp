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
	Client* client = m_screenManager->getClient();
	if (client->startWinSock())
	{
		if (client->createSocket())
		{

		}
	}
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Lobby::update(double dt)
{
	if (!m_connected)
	{
		connectToServer();
	}
}



/// <summary>
/// Start winsock and then attempt to connect to the server.
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
