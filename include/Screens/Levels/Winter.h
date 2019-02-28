#ifndef WINTER_H
#define WINTER_H

#include "Screens/Levels/Level.h"

class Winter : public Level
{
public:
	Winter(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;
private:
	virtual void spawnLevelObstacles() override;
	virtual void loadTextures() override;
};
#endif // !WINTER_H
