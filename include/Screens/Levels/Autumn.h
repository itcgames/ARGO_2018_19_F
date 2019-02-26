#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"
#include "AI/Grid.h"
#include <SDL_mixer.h>

class Autumn : public Screen
{
public:
	Autumn(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt, SDL_Event& e) override;
	virtual void render() override;
private:
	EntityManager m_entityManager;
	std::vector<Entity*> m_deaths;
	Vector m_startPos;
	Mix_Music * m_music;
	Mix_Chunk * m_effect;
	bool m_startMusic;
	int m_count;
};
#endif // !AUTUMN_H
