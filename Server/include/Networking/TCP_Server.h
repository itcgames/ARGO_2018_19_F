#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "Networking/Server.h"
#include <thread>

class TCPServer : public Server
{
public:
	TCPServer();
	virtual bool createSocket() override;
	virtual bool bindSocket() override;
	void acceptConnections();
	static void sendAndReceive(int sock, int * playerCount, SOCKET* clients);
	virtual void closeSocket() override;
};
#endif // !TCP_SERVER_H
