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
		std::cout << "<SERVER> Can't start Winsock!" << wsOk << std::endl;
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
	m_listening = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_listening == INVALID_SOCKET)
	{
		std::cout << "<SERVER> Can't create a socket!" << std::endl;
	}
	else
	{
		std::cout << "<SERVER> Created socket!" << std::endl;
		m_serverHint.sin_addr.S_un.S_addr = INADDR_ANY;
		m_serverHint.sin_family = AF_INET;
		m_serverHint.sin_port = htons(PORT);
		inet_pton(AF_INET, SERVER_IPS.at("dj"), &m_serverHint.sin_addr);
		if (bind(m_listening, (sockaddr*)&m_serverHint, sizeof(m_serverHint)) == SOCKET_ERROR)
		{
			std::cout << "<SERVER> Can't bind socket!" << WSAGetLastError() << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			std::cout << "<SERVER> Bound socket!" << std::endl;
			listen(m_listening, SOMAXCONN);
			FD_ZERO(&m_master);
			FD_SET(m_listening, &m_master);
			result = true;
		}
	}
	return result;
}



/// <summary>
/// 
/// </summary>
void Server::update()
{
	fd_set masterCopy = m_master;

	int socketCount = select(0, &masterCopy, nullptr, nullptr, nullptr);
	for (int i = 0; i < socketCount; i++)
	{
		SOCKET sock = masterCopy.fd_array[i];

		if (sock == m_listening)
		{
			SOCKET client = accept(m_listening, nullptr, nullptr);
			FD_SET(client, &m_master);
			playerCount++;
			Packet* packet = new Packet();
			packet->message = "New";
			packet->playerNum = playerCount;
			send(client, (char*)packet, sizeof(struct Packet) + 1, 0);
			std::cout << "playerNum:" << std::to_string(playerCount) << std::endl;
		}
		else
		{
			Packet* packet = new Packet();	
			ZeroMemory(packet, sizeof(struct Packet));

			int bytesIn = recv(sock, (char*)packet, sizeof(struct Packet), 0);
			if (bytesIn <= 0)
			{
				closesocket(sock);
				FD_CLR(sock, &m_master);
			}
			else
			{
				for (u_int j = 0; j < m_master.fd_count; j++)
				{
					SOCKET outSock = m_master.fd_array[j];
					if (outSock != m_listening && outSock != sock)
					{						
						send(outSock, (char*)packet, sizeof(struct Packet) + 1, 0);
					}
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
	FD_CLR(m_listening, &m_master);
	closesocket(m_listening);
	Packet* packet = new Packet();
	packet->message = "<Server> Shutting down \r\n";
	while (m_master.fd_count > 0)
	{
		SOCKET sock = m_master.fd_array[0];
		send(sock, (char*)packet, sizeof(struct Packet) + 1, 0);
		FD_CLR(sock, &m_master);
		closesocket(sock);
	}
	WSACleanup();
}