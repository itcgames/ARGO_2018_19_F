#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Vector/Vector.h"
#include "SDL.h"

class Node
{
public:
	Node();
	Node(Vector& pos);
	void render(SDL_Renderer* renderer);

	void setPosition(Vector& pos);
	Vector& getPosition();

private:
	Vector m_position;

	typedef int32_t s32;

	inline void DrawCircle(SDL_Renderer *Renderer, s32 _x, s32 _y, s32 radius)
	{
		s32 x = radius - 1;
		s32 y = 0;
		s32 tx = 1;
		s32 ty = 1;
		s32 err = tx - (radius << 1); // shifting bits left by 1 effectively
									  // doubles the value. == tx - diameter
		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
			SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
			SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
			SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
			SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
			SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
			SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
			SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

			if (err <= 0)
			{
				y++;
				err += ty;
				ty += 2;
			}
			if (err > 0)
			{
				x--;
				tx += 2;
				err += tx - (radius << 1);
			}
		}
	}
};
#endif // !NODE_H

