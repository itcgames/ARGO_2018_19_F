#ifndef SPRING_H
#define SPRING_H

#include "Screens/Screen.h"

class Spring : public Screen
{
public:
	Spring(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt, SDL_Event& e) override;
	virtual void render() override;
private:

};
#endif // !SPRING_H
