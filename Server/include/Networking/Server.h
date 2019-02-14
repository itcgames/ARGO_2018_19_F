#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 4

//	Standard.
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
//	Project.
#include "../../include//Networking/Packet.h"
#include "../../submodules/Vector/Vector.h"

class Server
{
public:
	inline Server() { playerCount = 0; }
	inline ~Server() { std::cout << "Deleted server" << std::endl; }

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline bool startWinSock()
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
	/// <returns></returns>
	virtual bool createSocket() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual bool bindSocket() = 0;
	
	/// <summary>
	/// 
	/// </summary>
	virtual void closeSocket() = 0;

protected:
	WSAData m_data;
	WORD m_version;
	SOCKET m_listening;
	sockaddr_in m_serverHint;

	bool m_serverOk;

	int playerCount;
	SOCKET m_client[MAX_CLIENTS];
	sockaddr m_client_sock[MAX_CLIENTS];
	int m_clientLength;

	const std::map<std::string, const char*> SERVER_IPS = { { "local", "127.0.0.1" },{ "john", "149.153.106.153" },{ "dj", "149.153.106.154" },{ "connor", "149.153.106.159" } };
	const int PORT = 54000;
};
#endif // !SERVER_H
