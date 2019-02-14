#ifndef SPLASH_H
#define SPLASH_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Entities/EntityCreator.h"

class Splash : public Screen
{
public:
	Splash(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	double m_clock;

	UIGraphicsSystem m_ui;
	std::vector<Entity*> m_entities;
};
#endif // !SPLASH_H
