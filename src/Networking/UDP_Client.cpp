#include "Networking\UDP_Client.h"

/// <summary>
/// 
/// </summary>
UDPClient::UDPClient()
{
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool UDPClient::createSocket()
{
	bool result = false;

	m_serverHint.sin_family = AF_INET;
	m_serverHint.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IPS.at("dj"), &m_serverHint.sin_addr);

	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
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
/// <param name="msg"></param>
/// <returns></returns>
bool UDPClient::sendMsg(Packet * msg)
{
	bool result = false;
	if (sizeof(msg) > 0)
	{
		int sendResult = sendto(m_socket, (char*)msg, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_serverHint, sizeof(m_serverHint));
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
Packet * UDPClient::recvMsg()
{
	Packet* packet = new Packet();
	int addr_len = sizeof(m_serverHint);
	int bytesReceived = recvfrom(m_socket, (char*)packet, sizeof(struct Packet), 0, (LPSOCKADDR)&m_serverHint, &addr_len);
	return packet;
}
