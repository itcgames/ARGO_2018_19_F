#ifndef CREDITS_H
#define CREDITS_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

class Credits : public Screen
{
public:
	Credits(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	double m_clock;
	EntityManager m_entityManager;
};
#endif // !CREDITS_H
