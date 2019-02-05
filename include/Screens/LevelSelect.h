#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H
//	Project
#include "Screens/Screen.h"

class LevelSelect : public Screen
{
public:
	LevelSelect();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !LEVEL_SELECT_H

