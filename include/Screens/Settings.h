#ifndef SETTINGS_H
#define SETTINGS_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

class Settings : public Screen
{
public:
	Settings(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	EntityManager m_entityManager;
};
#endif // !SETTINGS_H
