#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H
//	Project
#include "Screens/Screen.h"

class CharacterSelect : public Screen
{
public:
	CharacterSelect();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !CHARACTER_SELECT_H

