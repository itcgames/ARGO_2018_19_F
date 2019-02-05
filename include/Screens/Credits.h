#ifndef CREDITS_H
#define CREDITS_H
//	Project
#include "Screens/Screen.h"

class Credits : public Screen
{
public:
	Credits();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !CREDITS_H
