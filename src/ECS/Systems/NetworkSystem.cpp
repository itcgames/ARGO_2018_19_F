#include "ECS\Systems\NetworkSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="client"></param>
NetworkSystem::NetworkSystem(std::pair<std::string, Client*> client) :
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
	Packet* rPacket = m_client.second->recvMsg();
	if (rPacket->message == "New")
	{
		std::cout << "player " << rPacket->playerNum << " connected." << std::endl;
	}
	else
	{		
		for (Entity* entity : m_entities)
		{
			PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");
			PhysicsComponent* physics = (PhysicsComponent*)entity->getComponent("PHYSICS");
			NetworkComponent* network = (NetworkComponent*)entity->getComponent("NETWORK");
			ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");
			AnimationComponent* animation = (AnimationComponent*)entity->getComponent("ANIMATION");

			if (rPacket->playerNum == network->getPlayerNum() && rPacket->message == "Update" && controller == nullptr)
			{
				std::cout << "player " << rPacket->playerNum << " updated." << std::endl;
				position->setPos(rPacket->position);
				physics->setVelocity(rPacket->velocity);
				animation->setCurrentFrame(rPacket->currentFrame);
			}
			else if (controller != nullptr)
			{
				if (m_client.first == "TCP" && m_clock > SEND_DELAY)
				{
					Packet* sPacket = new Packet();

					sPacket->playerNum = network->getPlayerNum();
					sPacket->message = "Update";
					sPacket->position = Vector(position->getPos().x, position->getPos().y);

					m_client.second->sendMsg(sPacket);
					m_clock = 0;
				}
				else if (m_client.first == "UDP")
				{
					Packet* sPacket = new Packet();

					sPacket->playerNum = network->getPlayerNum();
					sPacket->message = "Update";
					sPacket->position = Vector(position->getPos().x, position->getPos().y);
					sPacket->currentFrame = animation->getCurrentFrame();

					m_client.second->sendMsg(sPacket);
					m_clock = 0;
				}				
			}
		}
	}	
}
