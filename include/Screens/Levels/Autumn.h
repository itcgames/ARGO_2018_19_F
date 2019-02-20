#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"
#include "Simple-SDL2-Audio/src/audio.h"

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
	Audio * music;
};
#endif // !AUTUMN_H
