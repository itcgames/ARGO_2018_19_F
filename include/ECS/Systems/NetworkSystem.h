#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/NetworkComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "Client.h"

class NetworkSystem : public System
{
public:
	NetworkSystem(Client* client);
	virtual void update(double dt) override;

private:
	Client * m_client;
	double m_clock;
};
#endif // !NETWORK_SYSTEM_H
