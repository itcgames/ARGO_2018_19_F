#ifndef NODE_PRIORITY_QUEUE_H
#define NODE_PRIORITY_QUEUE_H

#include "AI/NodeComparer.h"
#include "Vector/Vector.h"
#include <queue>
#include <vector>
#include <functional>
#include <stack>

class Vector;

template <typename VectorType, typename NodeType>
class NodePriorityQueue
{
public:
	NodePriorityQueue();
	NodePriorityQueue(NodeComparer<VectorType, NodeType> comparer);

	int compare(int a, int b);
	void swap(int a, int b);
	int push(VectorType& i);
	VectorType pop();
	void clear();
	int count();

private:
	std::vector<VectorType> m_queue;
	NodeComparer<VectorType, NodeType> m_comparer;
};

template<typename VectorType, typename NodeType>
NodePriorityQueue<VectorType, NodeType>::NodePriorityQueue()
{
	m_comparer = NodeComparer<VectorType, NodeType>();
}

template<typename VectorType, typename NodeType>
NodePriorityQueue<VectorType, NodeType>::NodePriorityQueue(NodeComparer<VectorType, NodeType> comparer)
{
	m_comparer = comparer;
}

template<typename VectorType, typename NodeType>
int NodePriorityQueue<VectorType, NodeType>::compare(int a, int b)
{
	return m_comparer.compare(m_queue[a], m_queue[b]);
}

template<typename VectorType, typename NodeType>
void NodePriorityQueue<VectorType, NodeType>::swap(int a, int b)
{
	std::swap(m_queue[a], m_queue[b]);
}

template<typename VectorType, typename NodeType>
int NodePriorityQueue<VectorType, NodeType>::push(VectorType& i)
{
	int a = m_queue.size();
	int b;

	m_queue.push_back(i);
	while (true)
	{
		if (a == 0)
			break;
		b = (a - 1) / 2;
		if (compare(a, b) < 0)
		{
			swap(a, b);
			a = b;
		}
		else
			break;
	}

	return a;
}

template<typename VectorType, typename NodeType>
VectorType NodePriorityQueue<VectorType, NodeType>::pop()
{
	VectorType result = m_queue[0];
	int a = 0;
	int b;
	int c;
	int d;

	m_queue[0] = m_queue[m_queue.size() - 1];
	m_queue.erase(std::remove(m_queue.begin(), m_queue.end(), m_queue[m_queue.size() - 1]), m_queue.end());
	while (true)
	{
		d = a;
		b = 2 * a + 1;
		c = 2 * a + 2;
		if (m_queue.size() > b && compare(a, b) > 0)
		{
			a = b;
		}
		if (m_queue.size() > c && compare(a, c) > 0)
		{
			a = c;
		}
		if (a == d)
		{
			break;
		}
		swap(a, d);
	}

	return result;
}

template<typename VectorType, typename NodeType>
void NodePriorityQueue<VectorType, NodeType>::clear()
{
	m_queue.clear();
}

template<typename VectorType, typename NodeType>
int NodePriorityQueue<VectorType, NodeType>::count()
{
	return m_queue.size();
}

#endif // !NODE_PRIORITY_QUEUE_H