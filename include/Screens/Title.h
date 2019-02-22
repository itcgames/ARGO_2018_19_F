#ifndef TITLE_H
#define TITLE_H

#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

class Title : public Screen
{
public:
	Title(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	EntityManager m_entityManager;
};
#endif // !TITLE_H
