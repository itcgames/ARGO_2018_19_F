#include "ECS\Systems\NetworkSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="client"></param>
NetworkSystem::NetworkSystem(UDPClient* client) :
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
	//	For each entity - 1 receive a msg.
	for (int i = 0; i < m_entities.size() - 1; i++)
	{
		Packet* rPacket = m_client->recvMsg();
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
					animation->m_flip = (SDL_RendererFlip)rPacket->flipped;
				}
			}
		}
	}
	
	//	
	for (Entity* entity : m_entities)
	{
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");
		PhysicsComponent* physics = (PhysicsComponent*)entity->getComponent("PHYSICS");
		NetworkComponent* network = (NetworkComponent*)entity->getComponent("NETWORK");
		ControllerComponent* controller = (ControllerComponent*)entity->getComponent("CONTROLLER");
		AnimationComponent* animation = (AnimationComponent*)entity->getComponent("ANIMATION");

		if (controller != nullptr)
		{
			Packet* sPacket = new Packet();

			sPacket->playerNum = network->getPlayerNum();
			sPacket->message = "Update";
			sPacket->position = Vector(position->getPos().x, position->getPos().y);
			sPacket->currentFrame = animation->getCurrentFrame();
			sPacket->flipped = animation->m_flip;

			m_client->sendMsg(sPacket);
		}
	}
}
