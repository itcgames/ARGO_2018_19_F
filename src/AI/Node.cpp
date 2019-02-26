#include "AI/Node.h"

Node::Node()
{
}


int Node::getHeuristic()
{
	return m_heuristic;
}

void Node::setHeuristic(int h)
{
	m_heuristic = h;
}

int Node::getEstimate()
{
	return m_estimate;
}

void Node::setEstimate(int e)
{
	m_estimate = e;
}

std::shared_ptr<Node> Node::getParent()
{
	return m_parent;
}

void Node::setParent(std::shared_ptr<Node> parent)
{
	m_parent = parent;
}

Vector Node::getParentIndex()
{
	return m_parentIndex;
}

void Node::setParentIndex(Vector parentIndex)
{
	m_parentIndex = parentIndex;
}

short Node::getJumpValue()
{
	return m_jumpValue;
}

void Node::setJumpValue(short value)
{
	m_jumpValue = value;
}

short Node::getStatus()
{
	return m_status;
}

void Node::setStatus(short status)
{
	m_status = status;
}