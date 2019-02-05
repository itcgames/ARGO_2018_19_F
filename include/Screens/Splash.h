#ifndef SPLASH_H
#define SPLASH_H
//	Project
#include "Screens/Screen.h"

class Splash : public Screen
{
public:
	Splash();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:
	double m_clock;
};
#endif // !SPLASH_H
