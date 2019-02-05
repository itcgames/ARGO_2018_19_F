#ifndef SUMMER_H
#define SUMMER_H

#include "Screens/Screen.h"

class Summer : public Screen
{
public:
	Summer(ScreenManager* screenManager);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !SUMMER_H
