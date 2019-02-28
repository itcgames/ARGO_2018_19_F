#include "Screens\Splash.h"

/// <summary>
/// 
/// </summary>
Splash::Splash(ScreenManager* screenManager, SDL_Renderer* renderer) :
	Screen(screenManager, renderer),
	m_entityManager(m_screenManager, renderer),
	m_playMusic(true)
{
	m_screenID = "Splash";

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 0, 2048) < 0)
	{
		std::cout << "error: " << Mix_GetError() << std::endl;
	}

	m_entityManager.createLabel(Vector(800, 250), "Scary Claus Studio", { 125,255,255 }, 400, 100);
	m_entityManager.createImage({600, 350}, SDL2Help::LoadTexture(m_resourcesPath + "Logo.png", m_renderer), {0, 0, 400, 400});
	m_bkg = Mix_LoadWAV("./resources//Sounds/backgroundMenuMusic.wav");
	//Mix_FreeChunk(m_bkg);
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Splash::update(double dt)
{
	m_clock += dt;
	if (m_playMusic)
	{
		//Mix_PlayChannel(1, m_bkg, -1);
		
		m_playMusic = false;
		
	}
	
	if (m_clock >= 3000)
	{
		m_screenManager->goToScreen("Title");
		m_clock = 0;
	}

	
}



/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void Splash::render()
{
	m_entityManager.render();
}
