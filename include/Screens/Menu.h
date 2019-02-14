#ifndef MENU_H
#define MENU_H
//	Project
#include "Screens/Screen.h"
#include "ECS/Entities/EntityCreator.h"

class Menu : public Screen
{
public:
	Menu(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	UIGraphicsSystem m_ui;
	std::vector<Entity*> m_entities;
};
#endif // !MENU_H
