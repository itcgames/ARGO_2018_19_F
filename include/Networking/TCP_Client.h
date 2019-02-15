#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include "Networking/Client.h"

class TCPClient : public Client
{
public:
	TCPClient();

	virtual bool createSocket() override;
	bool connectToServer();
	virtual bool sendMsg(Packet* msg) override;
	virtual Packet* recvMsg() override;
};
#endif // !TCP_CLIENT_H
