#ifndef SUMMER_H
#define SUMMER_H

#include "Screens/Levels/Level.h"

class Summer : public Level
{
public:
	Summer(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	virtual void spawnLevelObstacles() override;
	virtual void loadTextures() override;
};
#endif // !SUMMER_H
