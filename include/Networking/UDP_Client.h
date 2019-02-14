#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "Networking/Client.h"

class UDPClient : public Client
{
public:
	UDPClient();

	virtual bool createSocket() override;
	virtual bool sendMsg(Packet* msg) override;
	virtual Packet* recvMsg() override;
};
#endif // !UDP_CLIENT_H

