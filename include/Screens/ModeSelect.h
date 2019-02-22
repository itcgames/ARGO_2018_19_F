#ifndef MODE_SELECT_H
#define MODE_SELECT_H

#include "Screen.h"
#include "ECS/Entities/EntityManager.h"

class ModeSelect : public Screen
{
public:
	ModeSelect(ScreenManager* screenManager, SDL_Renderer* renderer);

	virtual void update(double dt) override;
	virtual void render() override;
private:
	EntityManager m_entityManager;
};
#endif // !MODE_SELECT_H
