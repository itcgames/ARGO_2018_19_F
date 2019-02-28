#ifndef PLAYER_STATE_SYSTEM
#define PLAYER_STATE_SYSTEM

#include "ECS/Systems/System.h"
#include "ECS/Components/PlayerStateComponent.h"

class PlayerStateSystem : public System
{
public:
	virtual void update(double dt) override;
	int getNumberOfPlayersStillPlaying();
private:
	int m_numberOfPlayersStillPlaying;
};
#endif // !PLAYER_STATE_SYSTEM
