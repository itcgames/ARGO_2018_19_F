#ifndef LOBBY_H
#define LOBBY_H

#include "Screen.h"
#include "ECS/Entities/EntityManager.h"

class Lobby : public Screen
{
public:
	Lobby(ScreenManager* screenManager, SDL_Renderer* renderer);

	virtual void update(double dt) override;
	virtual void render() override;

private:
	EntityManager m_entityManager;
};
#endif // !LOBBY_H
