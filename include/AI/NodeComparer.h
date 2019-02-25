#ifndef NODE_COMPARER_H
#define NODE_COMPARER_H

#include "AI/Node.h"

class NodeComparer
{
public:
	NodeComparer(std::vector<std::vector<Node*>> nodes)
	{
		m_nodes = nodes;
	}
	void compare(Vector& a, Vector& b)
	{
		if (m_nodes[a.x][a.y]);
	}

private:
	std::vector<std::vector<Node*>> m_nodes;
};

#endif // !NODE_COMPARER_H
