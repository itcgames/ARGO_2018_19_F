#include "AI/Node.h"

Node::Node(Vector location, int index)
{
	m_location = location;
	m_index = index;
	m_goal = false;
	m_start = false;
	m_shouldJump = false;
	m_goBack = false;
}

void Node::setStart(bool start)
{
	m_start = start;
}

bool Node::getStart()
{
	return m_start;
}

void Node::setGoal(bool start)
{
	m_goal = start;
}

bool Node::getGoal()
{
	return m_goal;
}

bool Node::getShouldJump()
{
	return m_shouldJump;
}

void Node::setShouldJump(bool jump)
{
	m_shouldJump = jump;
}

void Node::setVisited(bool visited)
{
	m_visited = visited;
}

bool Node::getVisited()
{
	return m_visited;
}

void Node::setGoBack(bool status)
{
	m_goBack = status;
}

Vector & Node::getLocation()
{
	return m_location;
}

void Node::setLocation(Vector location)
{
	m_location = location;
}

bool Node::getGoBack()
{
	return m_goBack;
}

std::shared_ptr<Node> Node::getNext()
{
	return m_next;
}

void Node::setNext(std::shared_ptr<Node> next)
{
	m_next.reset();
	m_next = next;
}

std::shared_ptr<Node> Node::getPrevious()
{
	return m_previous;
}

void Node::setPrevious(std::shared_ptr<Node> previous)
{
	m_previous.reset();
	m_previous = previous;
}
