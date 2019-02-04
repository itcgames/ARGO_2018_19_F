#ifndef GAME_H
#define GAME_H

#include "SDL2_Helper/SDL2Helper.h"
#include "Vector/Vector.h"
#include <iostream>
//	Systems


class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void update(double dt);
	void render();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;

	//	Entities.
	

	//	Systems.
	
};
#endif // GAME_H
