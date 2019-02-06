#ifndef CREDITS_H
#define CREDITS_H
//	Project
#include "Screens/Screen.h"

class Credits : public Screen
{
public:
	Credits(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:

};
#endif // !CREDITS_H
