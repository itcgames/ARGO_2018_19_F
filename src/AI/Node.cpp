#include "AI/Node.h"

Node::Node()
{
}

void Node::setPosition(Vector & pos)
{
	m_position = pos;
}

Vector & Node::getPosition()
{
	return m_position;
}

void Node::setWeight(float weight)
{
	m_weight = weight;
}

float Node::getWeight()
{
	return m_weight;
}

void Node::addNeighbour(Node * node)
{
	m_neighbours.push_back(node);
}

std::vector<Node*>& Node::getNeighbours()
{
	return m_neighbours;
}
