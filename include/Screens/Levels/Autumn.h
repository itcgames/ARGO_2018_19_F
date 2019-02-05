#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Screen.h"

class Autumn : public Screen
{
public:
	Autumn(ScreenManager* screenManager);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !AUTUMN_H
