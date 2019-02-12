#include "Server.h"

int main()
{
	Server server;
	if (server.startWinSock())
	{
		if (server.createAndBindSocket())
		{
			while (true)
			{
				server.update();
			}
		}
	}

	server.closeSocket();
	return 0;
}