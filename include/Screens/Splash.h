#ifndef SPLASH_H
#define SPLASH_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

class Splash : public Screen
{
public:
	Splash(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	double m_clock;

	EntityManager m_entityManager;
};
#endif // !SPLASH_H
