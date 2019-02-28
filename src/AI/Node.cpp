#include "AI/Node.h"

Node::Node()
{
}

Node::Node(Vector & pos)
{
	m_position = pos;
}

void Node::render(SDL_Renderer * renderer)
{
	DrawCircle(renderer, m_position.x, m_position.y, 5);
}

void Node::setPosition(Vector & pos)
{
	m_position = pos;
}

Vector & Node::getPosition()
{
	return m_position;
}
