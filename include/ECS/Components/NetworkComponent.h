#ifndef NETWORK_COMPONENT_H
#define NETWORK_COMPONENT_H

#include "ECS/Components/Component.h"

class NetworkComponent : public Component
{
public:
	NetworkComponent(int playerNum);

	int getPlayerNum();
private:
	int m_playerNum;
};
#endif // !NETWORK_COMPONENT_H
