#include "AI/Node.h"

Node::Node()
{
}

Node::Node(int x, int y, int width, int height)
{
	if (m_font == nullptr)
	{
		m_font = TTF_OpenFont(".//resources//AGENCYR.TTF", 50);
	}

	m_path = false;
	m_traversable = true;
	m_rect = new SDL_Rect({ x, y, width, height });
	m_location = Vector(x, y, 0);
	m_colour = { 125, 125, 0, 255 };
}

Node::Node(Vector & pos)
{
	m_location = pos;
}

void Node::addNeighbour(std::shared_ptr<Node> node)
{
	m_neighbours.push_back(node);
}

std::vector<std::shared_ptr<Node>>& Node::getNeighbours()
{
	// TODO: insert return statement here
	return m_neighbours;
}

//void Node::render(SDL_Renderer * renderer)
//{
//	SDL_Surface* surface = TTF_RenderText_Solid(m_font, _strdup(std::to_string(m_weight).c_str()), m_colour);
//	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
//
//	SDL_Rect dest = *m_rect;
//	dest.w = dest.w / 2;
//	dest.h = dest.h / 2;
//
//
//	SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
//	if (m_path)
//	{
//		SDL_RenderFillRect(renderer, m_rect);
//	}
//	else
//	{
//		SDL_RenderDrawRect(renderer, m_rect);
//	}
//
//	SDL_RenderCopy(renderer, message, NULL, &dest);
//	SDL_DestroyTexture(message);
//	SDL_FreeSurface(surface);
//}