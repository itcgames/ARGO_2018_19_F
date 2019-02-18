#include "Networking\UDP_Server.h"

/// <summary>
/// 
/// </summary>
UDPServer::UDPServer() :
	Server()
{
	
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool UDPServer::createSocket()
{
	bool result = false;
	m_listening = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_listening == INVALID_SOCKET)
	{
		std::cout << "<SERVER> Can't create a socket!" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "<SERVER> Created socket!" << std::endl;
		result = true;
	}
	return result;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool UDPServer::bindSocket()
{
	bool result = false;

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
		result = true;
	}
	return result;
}



/// <summary>
/// 
/// </summary>
void UDPServer::sendAndRecv()
{
	std::map<std::string, int> clientIpList;
	std::vector<sockaddr_in> clientList;
	sockaddr_in client;
	int clientLength = sizeof(struct sockaddr_in);
	Packet packet;

	while (TRUE)
	{
		ZeroMemory(&client, clientLength);
		ZeroMemory(&packet, sizeof(struct Packet));

		int bytesIn = recvfrom(m_listening, (char*)&packet, sizeof(struct Packet) + 1, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			std::cout << "<SERVER> Error receiving from client! " << WSAGetLastError() << std::endl;
		}
		else
		{
			char clientIp[256];
			ZeroMemory(&clientIp, 256);
			inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

			if (clientIpList[clientIp] == 0 || playerCount == 0)
			{
				playerCount++;
				clientIpList[clientIp] = playerCount;
				clientList.push_back(client);				
			}

			std::cout << "<SERVER> Message received from client at " << clientIp << "!" << std::endl;

			for (int i = 1; i <= playerCount; i++)
			{
				if (i != clientIpList[clientIp])
				{
					int sendOk = sendto(m_listening, (char*)&packet, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&clientList[i - 1], sizeof(clientList[i - 1]));
					if (sendOk == SOCKET_ERROR)
					{
						std::cout << "<SERVER> Error sending message! " << WSAGetLastError() << std::endl;
					}
					else
					{
						char sendIp[256];
						ZeroMemory(&sendIp, 256);
						inet_ntop(AF_INET, &clientList[i - 1].sin_addr, sendIp, 256);

						std::cout << "<SERVER> Message sent to client at " << sendIp << "!" << std::endl;
					}
				}
			}
		}
	}
}



/// <summary>
/// 
/// </summary>
void UDPServer::closeSocket()
{
	closesocket(m_listening);
	WSACleanup();
}
