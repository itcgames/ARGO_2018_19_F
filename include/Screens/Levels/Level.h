#ifndef LEVEL_H
#define LEVEL_H

#define MAX_PLAYERS 1

#include <random>

#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

enum ObstacleTypes
{
	Spike,
	Platform,
	Springboard,
	Teleporter,
	Dynamite,
	Bomb,
	Nuke,
	FerrisWheel,
	BallLauncher,
	HurleyMachine,
	Crossbow,
	last	//	This must always be the last on the list as it is used for picking one at random.
};

class Level : public Screen
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="screenManager"></param>
	/// <param name="renderer"></param>
	/// <param name="startPos"></param>
	/// <param name="endPos"></param>
	inline Level(ScreenManager* screenManager, SDL_Renderer* renderer, Vector startPos, Vector endPos) :
		Screen(screenManager, renderer),
		m_entityManager(screenManager, renderer)
	{
		m_startPos = startPos;
		m_endPos = endPos;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="dt"></param>
	virtual void update(double dt) = 0;

	/// <summary>
	/// 
	/// </summary>
	virtual void render() = 0;

protected:

	/// <summary>
	/// Spawns the players.
	/// </summary>
	/// <param name="controllablePlayers"></param>
	/// <param name="online"></param>
	virtual void spawnPlayers(int controllablePlayers, bool online)
	{
		//	Load all playerTextures
		loadTextures();

		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			bool controllable = false;
			std::pair<SDL_Rect, SDL_Texture*> pair = randomPlayerTexture(i);
			TextureAttributes textureAttributes = SDL2Help::getTextureAttributes(pair.second);
			SDL_Rect destRect = { 0, 0, 80, 96 };
			Vector animStart = {0, 0};
			Vector animEnd = {0, 0};

			if (i < controllablePlayers)
			{
				controllable = true;
			}

			m_entityManager.createPlayer(i, m_startPos, pair.second, pair.first, destRect, animStart, animEnd, destRect, controllable, online);
		}
	}

	/// <summary>
	/// Returns a random texture with colour based on player number.
	/// </summary>
	/// <param name="playerNum"></param>
	/// <returns></returns>
	virtual std::pair<SDL_Rect, SDL_Texture*> randomPlayerTexture(int playerNum)
	{
		std::string colour;
		if (playerNum == 0)
		{
			colour = "Red";
		}
		else if (playerNum == 1)
		{
			colour = "Blue";
		}
		else if (playerNum == 2)
		{
			colour = "Green";
		}
		else if (playerNum >= 3)
		{
			colour = "Yellow";
		}

		int sizeOfVec = m_playerTextures[colour].size();
		int random = rand() % sizeOfVec;
		return m_playerTextures[colour][random];
	}

	std::vector<Entity*> spawnNewObstacles()
	{
		int i = 0;
		std::vector<Entity*> newObstacles;
		while (i++ < 5)
		{
			Vector newObstaclePosition = {rand() % 1400, rand() % 700};
			ObstacleTypes newObstacleType = static_cast<ObstacleTypes>(rand() % ObstacleTypes::last);
			switch (newObstacleType)
			{
			case Spike:
				newObstacles.push_back(m_entityManager.returnObstacle(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "Obstacles//TriggeredSpike//TriggeredSpikeSheet.png", m_renderer), {0 ,0, 20, 100}, {0, 0, 20, 100}, "Spike", true, Vector( 0, 0 ), Vector( 0, 3 )));
				break;

			case Platform:
				newObstacles.push_back(m_entityManager.returnPlatform(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {0, 0, }, {0, 0, }));
				break;

			case Springboard:
				newObstacles.push_back(m_entityManager.returnPlatform(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}, "Spring"));
				break;

			case Teleporter:
				newObstacles.push_back(m_entityManager.returnPlatform(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}, "Teleporter"));
				break;

			case Dynamite:

				break;
			case Bomb:

				break;

			case Nuke:
				break;

			case FerrisWheel:
				break;

			case BallLauncher:
				m_entityManager.createAnimatedImage(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), { 0, 0, }, Vector(), Vector());
				break;

			case HurleyMachine:
				m_entityManager.createAnimatedImage(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), { 0, 0, }, Vector(), Vector());
				break;

			case Crossbow:
				m_entityManager.createAnimatedImage(newObstaclePosition, SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), { 0, 0, }, Vector(), Vector());
				break;

			case last:
				std::cout << "Oops!" << std::endl;
				break;

			default:
				break;
			}
		}
	}

	virtual void spawnLevelObstacles() = 0;
	virtual void loadTextures() = 0;

	EntityManager m_entityManager;

	Vector m_startPos;
	Vector m_endPos;

	std::map<std::string, std::vector<std::pair<SDL_Rect, SDL_Texture*>>> m_playerTextures;
};
#endif // !LEVEL_H
