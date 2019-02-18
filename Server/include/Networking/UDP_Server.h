#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "Networking/Server.h"

class UDPServer : public Server
{
public:
	UDPServer();

	virtual bool createSocket() override;
	virtual bool bindSocket() override;
	void sendAndRecv();
	virtual void closeSocket() override;
};
#endif // !UDP_SERVER_H
