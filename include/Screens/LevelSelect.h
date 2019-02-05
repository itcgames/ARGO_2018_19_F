#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H
//	Project
#include "Screens/Levels/Spring.h"
#include "Screens/Levels/Summer.h"
#include "Screens/Levels/Autumn.h"
#include "Screens/Levels/Winter.h"

class LevelSelect : public Screen
{
public:
	LevelSelect(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render(SDL_Renderer* renderer) override;
private:
	void setLevelToSpring();
	void setLevelToSummer();
	void setLevelToAutumn();
	void setLevelToWinter();

	SDL_Renderer* m_renderer;
};
#endif // !LEVEL_SELECT_H

