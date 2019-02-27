#ifndef NODE_COMPARER_H
#define NODE_COMPARER_H

#include "AI/Node.h"

class Node;

template<typename IntType, typename VectorType, typename NodeType>
class NodeComparer
{
public:
	inline NodeComparer()
	{
	}

	inline NodeComparer(std::vector<std::vector<NodeType>> nodes)
	{
		m_nodes = nodes;
	}

	inline void update(std::vector<std::vector<NodeType>> nodes)
	{
		m_nodes = nodes;
	}

	inline int compare(IntType iA, IntType iB, VectorType a, VectorType b)
	{
		if (m_nodes[iA][a.z]->getHeuristic() > m_nodes[iB][b.z]->getHeuristic())
		{
			return 1;
		}
		else if (m_nodes[iA][a.z]->getHeuristic() < m_nodes[iB][b.z]->getHeuristic())
		{
			return -1;
		}
		
		return 0;
	}

private:
	// list of vectors of nodes
	std::vector<std::vector<NodeType>> m_nodes;
};
#endif // !NODE_COMPARER_H
