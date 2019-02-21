#ifndef LEVEL_H
#define LEVEL_H

#define MAX_PLAYERS 4

#include <random>

#include "Screens/Screen.h"
#include "ECS/Entities/EntityManager.h"

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
			SDL_Rect srcRect = { 0, 0, textureAttributes.width, textureAttributes.height };
			SDL_Rect destRect = { 0, 0, 80, 96 };
			Vector animStart = {};
			Vector animEnd = {};

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

	virtual void spawnLevelObstacles() = 0;
	virtual void loadTextures() = 0;

	EntityManager m_entityManager;

	Vector m_startPos;
	Vector m_endPos;

	std::map<std::string, std::vector<SDL_Texture*>> m_playerTextures;
};
#endif // !LEVEL_H
