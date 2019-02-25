#include "ECS\Components\PlayerStateComponent.h"

/// <summary>
/// 
/// </summary>
PlayerStateComponent::PlayerStateComponent() :
	m_isAlive(true),
	m_hasWon(false)
{
	m_id = "PLAYER_STATE";
}



/// <summary>
/// Returns if the player is alive or not.
/// </summary>
/// <returns></returns>
bool PlayerStateComponent::isAlive()
{
	return m_isAlive;
}



/// <summary>
/// Sets if the player is alive or not.
/// </summary>
/// <param name="isAlive"></param>
void PlayerStateComponent::setAlive(bool isAlive)
{
	m_isAlive = isAlive;
}



/// <summary>
/// Returns if the player has reached the goal or not.
/// </summary>
/// <returns></returns>
bool PlayerStateComponent::hasWon()
{
	return m_hasWon;
}



/// <summary>
/// Sets if the player has reached the goal or not.
/// </summary>
/// <param name="hasWon"></param>
void PlayerStateComponent::setWon(bool hasWon)
{
	m_hasWon = hasWon;
}
