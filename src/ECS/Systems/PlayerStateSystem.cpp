#include "ECS\Systems\PlayerStateSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void PlayerStateSystem::update(double dt)
{
	m_numberOfPlayersStillPlaying = 0;
	for (Entity* entity : m_entities)
	{
		PlayerStateComponent* playerState = (PlayerStateComponent*)entity->getComponent("PLAYER_STATE");

		if (playerState != nullptr && (playerState->isAlive() && !playerState->hasWon()))
		{
			m_numberOfPlayersStillPlaying++;
		}
	}
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
int PlayerStateSystem::getNumberOfPlayersStillPlaying()
{
	return m_numberOfPlayersStillPlaying;
}
