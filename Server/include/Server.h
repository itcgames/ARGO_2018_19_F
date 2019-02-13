#ifndef SERVER_H
#define SERVER_H

#define MAX_CLIENTS 4

//	Standard.
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include <map>
#include <thread>
//	Project.
#include "../../include/Packet.h"
#include "../../submodules/Vector/Vector.h"

class Server
{
public:
	Server();
	~Server();
	bool startWinSock();
	bool createAndBindSocket();
	void acceptConnections();
	static void sendAndReceive(int sock, int * playerCount, SOCKET* clients);
	void closeSocket();

private:
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
