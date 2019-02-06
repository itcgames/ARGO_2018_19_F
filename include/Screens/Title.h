#ifndef TITLE_H
#define TITLE_H

#include "Screens/Screen.h"

class Title : public Screen
{
public:
	Title(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:

};
#endif // !TITLE_H
