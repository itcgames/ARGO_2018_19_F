#include "Client.h"

/// <summary>
/// 
/// </summary>
Client::Client()
{
}



/// <summary>
/// 
/// </summary>
Client::~Client()
{
}



/// <summary>
/// 
/// </summary>
bool Client::startWinSock()
{
	bool result = false;
	m_version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(m_version, &m_data);
	if (wsOk != 0)
	{
		std::cout << "<CLIENT> Can't start Winsock! " << wsOk << std::endl;
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
/// <returns></returns>
bool Client::createSocket()
{
	bool result = false;
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "<CLIENT> Can't create socket, Err #" << WSAGetLastError() << std::endl;
	}
	else
	{
		u_long mode = 1;
		ioctlsocket(m_socket, FIONBIO, &mode);
		result = true;
	}
	return result;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Client::connectToServer()
{
	bool result = false;
	m_serverHint.sin_family = AF_INET;
	m_serverHint.sin_port = htons(PORT);	
	inet_pton(AF_INET, SERVER_IPS.at("dj"), &m_serverHint.sin_addr);
	int connResult = connect(m_socket, (sockaddr*)&m_serverHint, sizeof(m_serverHint));
	if (connResult == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
	{
		std::cout << "<CLIENT> Can't connect to server, Err #" << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "<CLIENT> Connected to server" << std::endl;

		result = true;
	}

	return result;
}



/// <summary>
/// 
/// </summary>
/// <param name="msg"></param>
bool Client::sendMsg(Packet* msg)
{
	bool result = false;
	if (sizeof(msg) > 0)
	{
		int sendResult = send(m_socket, (char*)msg, sizeof(msg) + 1, 0);
		if (sendResult == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		{
			std::cout << "<CLIENT> Message failed to send, Err #" << WSAGetLastError() << std::endl;
		}
		else
		{
			result = true;
		}
	}
	return result;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Packet* Client::receiveMsg()
{
	Packet* packet = new Packet();
	recv(m_socket, (char*)packet, sizeof(packet), 0);
	return packet;
}



/// <summary>
/// 
/// </summary>
void Client::closeConnection()
{
	closesocket(m_socket);
	WSACleanup();
}
