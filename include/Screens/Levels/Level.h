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
			SDL_Texture* texture = randomPlayerTexture(i);
			TextureAttributes textureAttributes = SDL2Help::getTextureAttributes(texture);
			SDL_Rect srcRect = { 0, 0, 600, 925 };
			SDL_Rect destRect = { 0, 0, 80, 96 };
			Vector animStart = {0, 0};
			Vector animEnd = {3, 0};

			if (i < controllablePlayers)
			{
				controllable = true;
			}

			m_entityManager.createPlayer(i, m_startPos, texture, srcRect, destRect, animStart, animEnd, destRect, controllable, online);
		}
	}

	/// <summary>
	/// Returns a random texture with colour based on player number.
	/// </summary>
	/// <param name="playerNum"></param>
	/// <returns></returns>
	virtual SDL_Texture*  randomPlayerTexture(int playerNum)
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
		while (i++ < 5)
		{
			ObstacleTypes newObstacleType = static_cast<ObstacleTypes>(rand() % ObstacleTypes::last);
			switch (newObstacleType)
			{
			case Spike:
				m_entityManager.createObstacle(Vector(), SDL2Help::LoadTexture("", m_renderer), {}, {}, "Spike");
				break;
			case Platform:
				m_entityManager.createPlatform(Vector(), SDL2Help::LoadTexture("", m_renderer), {}, {});
				break;
			case Springboard:
				m_entityManager.createPlatform(Vector(), SDL2Help::LoadTexture("", m_renderer), {}, {}, "Spring");
				break;
			case Teleporter:
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
				break;
			case HurleyMachine:
				break;
			case Crossbow:
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

	std::map<std::string, std::vector<SDL_Texture*>> m_playerTextures;
};
#endif // !LEVEL_H
