#include "Server.h"

int main()
{
	Server* server = new Server();
	if (server->startWinSock())
	{
		if (server->createAndBindSocket())
		{
			server->acceptConnections();
		}
	}

	server->closeSocket();
	return 0;
}