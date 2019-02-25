#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Levels/Level.h"
#include <SDL_mixer.h>

class Autumn : public Level
{
public:
	Autumn(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;

private:
	virtual void spawnLevelObstacles() override;	
	virtual void loadTextures() override;

	Mix_Music * m_music;
	Mix_Chunk * m_effect;
	bool m_startMusic;

	bool m_gameInProgress;
	bool m_online;
	double m_clock;
};
#endif // !AUTUMN_H
