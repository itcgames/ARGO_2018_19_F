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
	m_clock += dt;
	Packet* rPacket = m_client->receiveMsg();
	if (rPacket->message == "New")
	{
		std::cout << "player " << rPacket->playerNum << " connected." << std::endl;
	}
	else
	{
		

		for (Entity* entity : m_entities)
		{
			PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");
			PhysicsComponent* physics = (PhysicsComponent*)entity->getComponent("");
			NetworkComponent* network = (NetworkComponent*)entity->getComponent("NETWORK");
			ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");

			if (rPacket->playerNum == network->getPlayerNum() && rPacket->message == "Update" && controller == nullptr)
			{
				std::cout << "player " << rPacket->playerNum << " updated." << std::endl;
				position->setPos(rPacket->position);
				physics->setVelocity(rPacket->velocity);
			}
			else if (controller != nullptr && m_clock > 100)
			{
				Packet* sPacket = new Packet();

				sPacket->playerNum = network->getPlayerNum();
				sPacket->message = "Update";
				sPacket->position = Vector(position->getPos().x, position->getPos().y);

				m_client->sendMsg(sPacket);
				m_clock = 0;
			}
		}
	}	
}
