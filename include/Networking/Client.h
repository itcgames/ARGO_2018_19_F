#ifndef CLIENT_H
#define CLIENT_H
//	Standard.
#include <WS2tcpip.h>
#include <map>
#include <string>
#include <iostream>
//	Project.
#include "Packet.h"

class Client
{
public:
	inline Client() {}
	inline ~Client() {}
	
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline bool startWinsock()
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
	virtual bool createSocket() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="msg"></param>
	/// <returns></returns>
	virtual bool sendMsg(Packet* msg) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual Packet* recvMsg() = 0;
	
	/// <summary>
	/// 
	/// </summary>
	inline void closeSocket()
	{
		closesocket(m_socket);
		WSACleanup();
	}

protected:
	WSAData m_data;
	WORD m_version;
	SOCKET m_socket;

	sockaddr_in m_serverHint;
	const std::map<std::string, const PCSTR> SERVER_IPS = { { "local", "127.0.0.1" },{ "john", "149.153.106.153" },{ "dj", "149.153.106.154" },{ "connor", "149.153.106.159" } };
	const int PORT = 54000;
};
#endif // !CLIENT_H
