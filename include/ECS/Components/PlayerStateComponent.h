#ifndef PLAYER_STATE_COMPONENT
#define PLAYER_STATE_COMPONENT

#include "ECS/Components/Component.h"

class PlayerStateComponent : public Component
{
public:
	PlayerStateComponent();

	bool isAlive();
	void setAlive(bool isAlive);

	bool hasWon();
	void setWon(bool hasWon);

private:
	bool m_isAlive;
	bool m_hasWon;
};
#endif // !PLAYER_STATE_COMPONENT
