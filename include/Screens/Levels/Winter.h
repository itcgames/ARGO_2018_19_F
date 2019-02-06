#ifndef WINTER_H
#define WINTER_H

#include "Screens/Screen.h"

class Winter : public Screen
{
public:
	Winter(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt, SDL_Event& e) override;
	virtual void render() override;
private:

};
#endif // !WINTER_H
