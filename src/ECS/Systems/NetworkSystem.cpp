#include "ECS\Systems\NetworkSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="client"></param>
NetworkSystem::NetworkSystem(Client * client) :
	m_client(client)
{

}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void NetworkSystem::update(double dt)
{
	Packet* rPacket = m_client->receiveMsg();
	for (Entity* entity : m_entities)
	{
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");	
		NetworkComponent* network = (NetworkComponent*)entity->getComponent("NETWORK");
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");

		if (rPacket->playerNum == network->getPlayerNum() && rPacket->message == "Update" && controller == nullptr)
		{
			position->setPos(rPacket->position);
		}
		else if (controller != nullptr)
		{
			Packet* sPacket = new Packet();
			sPacket->playerNum = network->getPlayerNum();
			sPacket->message = "Update";
			sPacket->position = Vector(position->getPos().x, position->getPos().y);
			m_client->sendMsg(sPacket);
		}
	}
}
