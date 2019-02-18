#include "ECS\Components\NetworkComponent.h"

/// <summary>
/// 
/// </summary>
/// <param name="playerNum"></param>
NetworkComponent::NetworkComponent(int playerNum) :
	m_playerNum(playerNum)
{
	m_id = "NETWORK";
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int NetworkComponent::getPlayerNum()
{
	return m_playerNum;
}
