#ifndef WINTER_H
#define WINTER_H

#include "Screens/Screen.h"

class Winter : public Screen
{
public:
	Winter(ScreenManager* screenManager);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !WINTER_H
