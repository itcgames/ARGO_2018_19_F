/// <summary>
/// @mainpage ARGO
/// @Authors D.J. O'Leary, John O'Grady, Conor O'Toole
/// @Version 1.0
/// @brief 
/// </summary>

#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream> 
#include <SDL_mixer.h>

//	Entry point.
int main(int argc, char* argv[])
{
	//	Init Everything.
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_AllocateChannels(30);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	Game* game;
	game = new Game();
	game->run();

	return 1;
}