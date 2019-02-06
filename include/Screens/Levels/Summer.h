#ifndef SUMMER_H
#define SUMMER_H

#include "Screens/Screen.h"

class Summer : public Screen
{
public:
	Summer(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt, SDL_Event& e) override;
	virtual void render() override;
private:

};
#endif // !SUMMER_H
