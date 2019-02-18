#include "Networking/TCP_Client.h"

/// <summary>
/// 
/// </summary>
TCPClient::TCPClient()
{

}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool TCPClient::createSocket()
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
bool TCPClient::connectToServer()
{
	bool result = false;

	m_serverHint.sin_family = AF_INET;
	inet_pton(AF_INET, SERVER_IPS.at("dj"), &m_serverHint.sin_addr);
	m_serverHint.sin_port = htons(PORT);	

	int connResult = connect(m_socket, (LPSOCKADDR)&m_serverHint, sizeof(m_serverHint));
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
bool TCPClient::sendMsg(Packet* msg)
{
	bool result = false;
	if (sizeof(msg) > 0)
	{
		int sendResult = send(m_socket, (char*)msg, sizeof(struct Packet) + 1, 0);
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
Packet* TCPClient::recvMsg()
{
	Packet* packet = new Packet();
	int addr_len = sizeof(m_serverHint);
	int bytesReceived = recv(m_socket, (char*)packet, sizeof(struct Packet), 0);
	return packet;
}
