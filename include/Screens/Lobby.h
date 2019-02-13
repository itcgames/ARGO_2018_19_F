#ifndef LOBBY_H
#define LOBBY_H

#include "Screen.h"

class Lobby : public Screen
{
public:
	Lobby(ScreenManager* screenManager, SDL_Renderer* renderer);

	virtual void update(double dt) override;
	virtual void render() override;
private:
	void connectToServer();
	bool m_connected;
};
#endif // !LOBBY_H
