#ifndef NODE_COMPARER_H
#define NODE_COMPARER_H

#include "AI/Node.h"

template<typename NodeType>
class NodeComparer
{
public:
	inline NodeComparer(std::vector<std::vector<std::shared_ptr<NodeType>>>& nodes)
	{
		m_nodes = nodes;
	}

	inline int compare(Location a, Location b)
	{
		if (m_nodes[a.xy][a.z]->getHeuristic() > m_nodes[b.xy][b.z]->getHeuristic())
		{
			return 1;
		}
		else if (m_nodes[a.xy][a.z]->getHeuristic() < m_nodes[b.xy][b.z]->getHeuristic())
		{
			return -1;
		}
		
		return 0;
	}

private:
	std::vector<std::vector<std::shared_ptr<NodeType>>> m_nodes;
};

#endif // !NODE_COMPARER_H
