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
	Crossbow
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

		if (MAX_PLAYERS <= 3)
		{
			std::pair<SDL_Rect, SDL_Texture*> pair = randomPlayerTexture(MAX_PLAYERS);
			TextureAttributes textureAttributes = SDL2Help::getTextureAttributes(pair.second);
			SDL_Rect destRect = { 0, 0, 80, 96 };
			Vector animStart = { 0, 0 };
			Vector animEnd = { 0, 0 };

			m_entityManager.createAI(m_startPos, pair.second, pair.first, destRect, animStart, animEnd, destRect);
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

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::vector<Entity*> generateNewObstacles()
	{
		m_generatedNewObstacles = true;
		int i = 0;
		std::vector<Entity*> newObstacles;
		while (i++ < 5)
		{
			int x = rand() % 1400;
			int y = rand() % 700;
			int newObstacleType = rand() % 100 + 1;

			//	Platform - 20% chance.
			if (newObstacleType <= 100)
			{
				newObstacles.push_back(m_entityManager.returnPlatform(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "Obstacles//Platforms//Tetris I Rotated.png", m_renderer), {0, 0, 200, 40}, {0, 0, 200, 40}, "I"));
			}
			//	Spike - 10% chance.
			else if (newObstacleType <= 30)
			{
				newObstacles.push_back(m_entityManager.returnObstacle(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}));
			}
			//	Springboard - 10% chance.
			else if (newObstacleType <= 40)
			{
				newObstacles.push_back(m_entityManager.returnPlatform(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}));
			}
			//	Teleporter - 5% chance.
			else if (newObstacleType <= 45)
			{
				newObstacles.push_back(m_entityManager.returnObstacle(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}));;
			}
			//	Dynamite - 10% chance.
			else if (newObstacleType <= 55)
			{
				//	A removal object needs to be added, supporting functions are already in place.
				//	newObstacles.push_back();
			}
			//	Bomb - 5% chance.
			else if (newObstacleType <= 60)
			{
				//	A removal object needs to be added, supporting functions are already in place.
				//	newObstacles.push_back();
			}
			//	Nuke - 5% chance.
			else if (newObstacleType <= 65)
			{
				//	A removal object needs to be added, supporting functions are already in place. 
				//	newObstacles.push_back();
			}
			//	Ferriswheel - 10% chance.
			else if (newObstacleType <= 75)
			{
				newObstacles.push_back(m_entityManager.returnPlatform(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}));
			}
			//	Ball launcher - 5% chance.
			else if (newObstacleType <= 80)
			{
				newObstacles.push_back(m_entityManager.returnEmitter(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}, Vector(), Vector()));
			}
			//	Hurley machine - 10% chance.
			else if (newObstacleType <= 90)
			{
				newObstacles.push_back(m_entityManager.returnEmitter(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}, Vector(), Vector()));
			}
			//	Crossbow - 10% chance.
			else if (newObstacleType <= 100)
			{
				newObstacles.push_back(m_entityManager.returnEmitter(Vector(x, y), SDL2Help::LoadTexture(m_resourcesPath + "", m_renderer), {}, {}, Vector(), Vector()));
			}
		}

		return newObstacles;
	}

	virtual void spawnLevelObstacles() = 0;
	virtual void loadTextures() = 0;

	EntityManager m_entityManager;

	Vector m_startPos;
	Vector m_endPos;

	std::vector<Entity*> m_newObstacles;
	bool m_generatedNewObstacles;

	std::map<std::string, std::vector<std::pair<SDL_Rect, SDL_Texture*>>> m_playerTextures;
};
#endif // !LEVEL_H
