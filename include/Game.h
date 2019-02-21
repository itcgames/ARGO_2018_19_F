#ifndef GAME_H
#define GAME_H
//	Standard.
#include <iostream>
//	Project.
#include "SDL2_Helper/SDL2Helper.h"
#include "Vector/Vector.h"
/*			Screens				*/
#include "Screens/ScreenManager.h"
#include "Screens/Splash.h"
#include "Screens/Title.h"
#include "Screens/Menu.h"
#include "Screens/ModeSelect.h"
#include "Screens/LevelSelect.h"
#include "Screens/Levels/Winter.h"
#include "Screens/Settings.h"
#include "Screens/Credits.h"
#include "Screens/Lobby.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void update(double dt, SDL_Event &e);
	void render();

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;	

	ScreenManager m_screenManager;
};
#endif // GAME_H
