#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Vector/Vector.h"
#include "SDL.h"
#include <string>
#include "SDL_ttf.h"

class Node
{
public:
	Node();
	Node(int x, int y, int width, int height);
	Node(Vector& pos);

	// getters and setters
	int getHeuristic();
	void setHeuristic(int h);


	void addNeighbour(Node* node);
	std::vector<Node*>& getNeighbours();

private:
	// visualisation
	TTF_Font * m_font;
	SDL_Color m_colour;

	// node logic
	SDL_Rect* m_rect; // used for detection of world obstacles
	Vector m_location; // location and jump value within the grid
	std::vector<Node*> m_neighbours; // adjacent cells

	Node* m_parent; // parent node that we got to his node from
	Vector m_parentIndex; // used to get the parent in neighbours list
	int m_weight; // weight of the node
	int m_heuristic; // F - a star hueristic
	short m_G; // ??
	short m_status; // nodes open / closed status
	short m_jumpLength; // the current jump distance of the node

	// future 
	bool m_traversable;
	bool m_path;

	//void setLocation(Vector& location);
	//SDL_Rect* getRect();
	//Vector& getLocation();
	//void setGoal();
	//void setStart();
	//void setPath();
	//void setWeight(int weight);
	//void setTraversable(bool traversable);
	//bool getTraversable();
	//void render(SDL_Renderer* renderer);

	//typedef int32_t s32;
	//inline void DrawCircle(SDL_Renderer *Renderer, s32 _x, s32 _y, s32 radius)
	//{
	//	s32 x = radius - 1;
	//	s32 y = 0;
	//	s32 tx = 1;
	//	s32 ty = 1;
	//	s32 err = tx - (radius << 1); // shifting bits left by 1 effectively
	//								  // doubles the value. == tx - diameter
	//	while (x >= y)
	//	{
	//		//  Each of the following renders an octant of the circle
	//		SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
	//		SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
	//		SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
	//		SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
	//		SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
	//		SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
	//		SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
	//		SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

	//		if (err <= 0)
	//		{
	//			y++;
	//			err += ty;
	//			ty += 2;
	//		}
	//		if (err > 0)
	//		{
	//			x--;
	//			tx += 2;
	//			err += tx - (radius << 1);
	//		}
	//	}
	//}
};
#endif // !NODE_H

