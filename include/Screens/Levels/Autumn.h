#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Levels/Level.h"

class Autumn : public Level
{
public:
	Autumn(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;

private:
	virtual void spawnLevelObstacles() override;	
	virtual void loadTextures() override;
};
#endif // !AUTUMN_H
