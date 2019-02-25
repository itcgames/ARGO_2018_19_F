#ifndef NODE_COMPARER_H
#define NODE_COMPARER_H

#include "AI/Node.h"

template<class Node>
class NodeComparer
{
public:
	inline NodeComparer(std::vector<std::vector<Node*>>& nodes)
	{
		m_nodes = nodes;
	}

	inline int compare(Vector& a, Vector& b)
	{
		if (m_nodes[a.x][a.y]->getHeuristic() > m_nodes[b.x][b.y]->getHeuristic())
		{
			return 1;
		}
		else if (m_nodes[a.x][a.y]->getHeuristic() < m_nodes[b.x][b.y]->getHeuristic())
		{
			return -1;
		}
		
		return 0;
	}

private:
	std::vector<std::vector<Node*>> m_nodes;
};

#endif // !NODE_COMPARER_H
