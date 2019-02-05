#ifndef TITLE_H
#define TITLE_H

#include "Screens/Screen.h"

class Title : public Screen
{
public:
	Title();
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:

};
#endif // !TITLE_H
