#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H
//	Project
#include "Screens/Screen.h"

class CharacterSelect : public Screen
{
public:
	CharacterSelect(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:

};
#endif // !CHARACTER_SELECT_H

