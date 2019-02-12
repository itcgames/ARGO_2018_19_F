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
	Client();
	~Client();
	bool startWinSock();
	bool createSocket();
	bool connectToServer();
	bool sendMsg(Packet* msg);
	Packet* receiveMsg();
	void closeConnection();
private:
	WSAData m_data;
	WORD m_version;
	SOCKET m_socket;

	sockaddr_in m_serverHint;
	const std::map<std::string, const PCSTR> SERVER_IPS = { {"local", "127.0.0.1"}, {"john", "149.153.106.153"}, {"dj", "149.153.106.154"}, {"connor", "149.153.106.159"} };
	const int PORT = 54000;
};
#endif // !CLIENT_H
