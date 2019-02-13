#include "Server.h"

/// <summary>
/// 
/// </summary>
Server::Server() :
	playerCount(0)
{

}



/// <summary>
/// 
/// </summary>
Server::~Server()
{
}



/// <summary>
/// 
/// </summary>
bool Server::startWinSock()
{
	bool result = false;
	m_version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(m_version, &m_data);
	if (wsOk != 0)
	{
		std::cout << "<SERVER> Can't start Winsock! " << wsOk << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "<SERVER> Started Winsock!" << std::endl;
		result = true;
	}
	return result;
}



/// <summary>
/// 
/// </summary>
bool Server::createAndBindSocket()
{
	bool result = false;
	m_listening = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listening == INVALID_SOCKET)
	{
		std::cout << "<SERVER> Can't create a socket!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "<SERVER> Created socket!" << std::endl;

		m_serverHint.sin_family = AF_INET;
		inet_pton(AF_INET, SERVER_IPS.at("dj"), &m_serverHint.sin_addr);
		m_serverHint.sin_port = htons(PORT);

		if (bind(m_listening, (LPSOCKADDR)&m_serverHint, sizeof(m_serverHint)) == SOCKET_ERROR)
		{
			std::cout << "<SERVER> Can't bind socket! " << WSAGetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			std::cout << "<SERVER> Bound socket!" << std::endl;

			listen(m_listening, 3);
			result = true;
		}
	}
	return result;
}



/// <summary>
/// 
/// </summary>
void Server::acceptConnections()
{
	int addr_size = sizeof(struct sockaddr);
	while (playerCount < MAX_CLIENTS)
	{
		m_client[playerCount] = accept(m_listening, &m_client_sock[playerCount], &addr_size);

		if (m_client[playerCount] == INVALID_SOCKET)
		{
			std::cout << "<SERVER> Client failed to connect!" << std::endl;
		}
		else
		{
			//	Create a seperate thread.
			std::thread t(&sendAndReceive, playerCount, &playerCount, m_client);
			
			//	Update the player count and send a packet to the client.			
			Packet* packet = new Packet();
			packet->message = "New";
			packet->playerNum = playerCount;
			send(m_client[playerCount], (char*)packet, sizeof(struct Packet) + 1, 0);
			std::cout << "playerNum:" << std::to_string(playerCount + 1) << std::endl;
			playerCount++;
			//	Detach the thread.
			t.detach();					
		}
	}
}



/// <summary>
/// 
/// </summary>
void Server::sendAndReceive(int sock, int* playerCount, SOCKET* clients)
{
	SOCKET client = clients[sock];
	while (client)
	{
		//	Create packet in memory.
		Packet* packet = new Packet();
		ZeroMemory(packet, sizeof(struct Packet));
		//	Fill in the packet with the received bytes.
		int bytesIn = recv(client, (char*)packet, sizeof(struct Packet), 0);

		if (bytesIn <= 0)
		{
			shutdown(client, SD_SEND);
			closesocket(client);
		}
		else
		{
			for (int j = 0; j < *playerCount; j++)
			{
				SOCKET outSock = clients[j];
				if (outSock != client)
				{
					send(outSock, (char*)packet, sizeof(struct Packet) + 1, 0);
				}
			}
		}	
	}
}



/// <summary>
/// 
/// </summary>
void Server::closeSocket()
{
	closesocket(m_listening);
	Packet* packet = new Packet();
	packet->message = "<Server> Shutting down \r\n";
	for (int i = 0; i < playerCount; i++)
	{
		SOCKET client = m_client[i];
		send(client, (char*)packet, sizeof(struct Packet) + 1, 0);

		shutdown(client, SD_BOTH);
		closesocket(client);
	}
	WSACleanup();
}