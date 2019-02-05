#ifndef PLAY_H
#define PLAY_H
//	Project
#include "Screens/Screen.h"

class Play : public Screen
{
public:
	Play();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !PLAY_H
