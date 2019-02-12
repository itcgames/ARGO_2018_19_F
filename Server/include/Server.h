#ifndef SERVER_H
#define SERVER_H
//	Standard.
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
//	Project.
#include "../../include/Packet.h"

class Server
{
public:
	Server();
	~Server();
	bool startWinSock();
	bool createAndBindSocket();
	void update();
	void closeSocket();

private:
	WSAData m_data;
	WORD m_version;
	SOCKET m_listening;
	sockaddr_in m_serverHint;
	fd_set m_master;

	bool m_serverOk;

	int playerCount;
	sockaddr_in m_client;
	int m_clientLength;
	const std::map<std::string, const PCSTR> SERVER_IPS = { { "local", "127.0.0.1" },{ "john", "149.153.106.153" },{ "dj", "149.153.106.154" },{ "connor", "149.153.106.159" } };
	const int PORT = 54000;
};
#endif // !SERVER_H
