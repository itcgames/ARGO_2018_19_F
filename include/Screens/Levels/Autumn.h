#ifndef AUTUMN_H
#define AUTUMN_H

#include "Screens/Levels/Level.h"
#include "AI/Grid.h"

class Autumn : public Level
{
public:
	Autumn(ScreenManager* screenManager, SDL_Renderer* renderer);
	virtual void update(double dt) override;
	virtual void render() override;

private:
	virtual void spawnLevelObstacles() override;	
	virtual void loadTextures() override;

	bool m_gameInProgress;
	bool m_online;
	double m_clock;

	std::vector<Entity*> m_deaths;
	
	int m_count;
};
#endif // !AUTUMN_H
