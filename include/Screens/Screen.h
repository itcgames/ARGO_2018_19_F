#ifndef SCREEN_H
#define SCREEN_H
//	Standard.
#include <string>
//	Project.
#include "SDL.h"
#include "SDL2_Helper/SDL2Helper.h"

class Screen
{
public:
	inline Screen() {}
	inline ~Screen() {}

	virtual void reset() {};
	virtual void update(double dt, SDL_Event e) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	inline std::string getID() { return m_screenID; }
protected:
	std::string m_screenID;
	std::string m_resourcesPath = "resources/";
};
#endif // !SCREEN_H
