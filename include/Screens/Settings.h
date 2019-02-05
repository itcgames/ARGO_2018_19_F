#ifndef SETTINGS_H
#define SETTINGS_H
//	Project
#include "Screens/Screen.h"

class Settings : public Screen
{
public:
	Settings();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !SETTINGS_H
