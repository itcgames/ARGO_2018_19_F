#include "Server.h"

int main()
{
	Server server;
	if (server.startWinSock())
	{
		if (server.createAndBindSocket())
		{
			bool running = true;
			while (running)
			{
				server.update();
			}
		}
	}

	server.closeSocket();
	return 0;
}