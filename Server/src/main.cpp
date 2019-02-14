#include "Networking/TCP_Server.h"
#include "Networking/UDP_Server.h"
#include <iostream>

int main()
{
	while (TRUE)
	{
		std::cout << "What protocol do you wish to use?" << std::endl;
		std::string input;
		std::cin >> input;

		if (input == "TCP" || input == "tcp" || input == "Tcp")
		{
			TCPServer* tcpServer = new TCPServer();
			if (tcpServer->startWinSock())
			{
				if (tcpServer->createSocket())
				{
					if (tcpServer->bindSocket())
					{
						tcpServer->acceptConnections();
					}
				}
			}

			tcpServer->closeSocket();
		}
		else if (input == "UDP" || input == "udp" || input == "Udp")
		{
			UDPServer* udpServer = new UDPServer();
			if (udpServer->startWinSock())
			{
				if (udpServer->createSocket())
				{
					if (udpServer->bindSocket())
					{
						udpServer->sendAndRecv();
					}
				}
			}

			udpServer->closeSocket();
		}
	}
	
	return 0;
}