#ifndef SPRING_H
#define SPRING_H

#include "Screens/Levels/Level.h"

class Spring : public Level
{
public:
	Spring(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;

private:
	virtual void spawnLevelObstacles() override;
	virtual void loadTextures() override;
};
#endif // !SPRING_H
