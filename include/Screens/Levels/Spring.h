#ifndef SPRING_H
#define SPRING_H

#include "Screens/Screen.h"

class Spring : public Screen
{
public:
	Spring(ScreenManager* screenManager);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !SPRING_H
