#ifndef NETWORK_SYSTEM_H
#define NETWORK_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/NetworkComponent.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/AnimationComponent.h"

#include "Networking/UDP_Client.h"

class NetworkSystem : public System
{
public:
	NetworkSystem(UDPClient* client);
	virtual void update(double dt) override;

private:
	UDPClient* m_client;
	double m_clock;

	const int SEND_DELAY = 35;
};
#endif // !NETWORK_SYSTEM_H
