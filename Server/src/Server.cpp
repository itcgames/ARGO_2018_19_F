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
	}
	else
	{
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
	}
	else
	{
		m_serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
		m_serverHint.sin_family = AF_INET;
		m_serverHint.sin_port = htons(PORT);
		inet_pton(AF_INET, SERVER_IP, &m_serverHint.sin_addr);
		if (bind(m_listening, (sockaddr*)&m_serverHint, sizeof(m_serverHint)) == SOCKET_ERROR)
		{
			std::cout << "<SERVER> Can't bind socket! " << WSAGetLastError() << std::endl;
		}
		else
		{
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
			std::string message = "playerNum:" + std::to_string(playerCount);
			send(client, message.c_str(), message.size() + 1, 0);
			std::cout << message << std::endl;
		}
		else
		{
			char buf[4096];
			ZeroMemory(buf, 4096);

			int bytesIn = recv(sock, buf, sizeof(buf), 0);
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
						std::ostringstream ss;
						ss << buf << "\r\n";
						std::string strOut = ss.str();

						send(outSock, strOut.c_str(), strOut.size() + 1, 0);
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
	std::string msg = "<Server> Shutting down \r\n";
	while (m_master.fd_count > 0)
	{
		SOCKET sock = m_master.fd_array[0];
		send(sock, msg.c_str(), msg.size() + 1, 0);
		FD_CLR(sock, &m_master);
		closesocket(sock);
	}
	WSACleanup();
}