#ifndef SERVER_H
#define SERVER_H

#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>

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
	const PCSTR SERVER_IP = "127.0.0.1";
	const int PORT = 54000;
};
#endif // !SERVER_H