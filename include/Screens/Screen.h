#ifndef SCREEN_H
#define SCREEN_H
//	Standard.
#include <string>
//	Project.
#include "SDL.h"
#include "Screens/ScreenManager.h"
#include "SDL2_Helper/SDL2Helper.h"

class Screen
{
public:
	inline Screen(ScreenManager* screenManager, SDL_Renderer* renderer) : 
		m_screenManager(screenManager),
		m_renderer(renderer)
	{
	}
	inline ~Screen() {}

	virtual void reset() {};

	virtual void update(double dt) {};
	virtual void update(double dt, SDL_Event& e) {};
	virtual void render() = 0;

	inline std::string getID() { return m_screenID; }
protected:
	std::string m_screenID;
	ScreenManager* m_screenManager;
	SDL_Renderer* m_renderer;
	std::string m_resourcesPath = ".//resources//";
};
#endif // !SCREEN_H
