#ifndef SCREEN_H
#define SCREEN_H
//	Standard.
#include <string>
//	Project.
#include "SDL.h"

class Screen
{
public:
	inline Screen() {}
	inline ~Screen() {}

	virtual void reset() {};
	virtual void update(double dt) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	inline std::string getID() { return m_screenID; }
protected:
	std::string m_screenID;
};
#endif // !SCREEN_H
