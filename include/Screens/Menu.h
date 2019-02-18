#ifndef MENU_H
#define MENU_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

class Menu : public Screen
{
public:
	Menu(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	EntityManager m_entityManager;
};
#endif // !MENU_H
