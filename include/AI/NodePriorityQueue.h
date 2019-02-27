#ifndef NODE_PRIORITY_QUEUE_H
#define NODE_PRIORITY_QUEUE_H

#include "AI/NodeComparer.h"
#include <queue>
#include <vector>
#include <functional>
#include <stack>

template <typename IntType, typename VectorType, typename NodeType>
class NodePriorityQueue
{
public:
	NodePriorityQueue();
	NodePriorityQueue(NodeComparer<IntType, VectorType, NodeType> comparer);
	int compare(int a, int b);
	void swap(int a, int b);
	int push(IntType index, VectorType vector, std::vector<std::vector<NodeType>> nodes);
	std::pair<IntType, VectorType> pop();
	void clear();
	int count();
	std::vector<std::pair<IntType, VectorType>> getQueue();

private:
	std::vector<std::pair<IntType,VectorType>> m_queue;
	NodeComparer<IntType, VectorType, NodeType> m_comparer;
};

template <typename IntType, typename VectorType, typename NodeType>
NodePriorityQueue<IntType,VectorType, NodeType>::NodePriorityQueue()
{
	m_comparer = NodeComparer<IntType, VectorType, NodeType>();
}

template <typename IntType, typename VectorType, typename NodeType>
NodePriorityQueue<IntType, VectorType, NodeType>::NodePriorityQueue(NodeComparer<IntType,VectorType, NodeType> comparer)
{
	m_comparer = comparer;
}

template <typename IntType, typename VectorType, typename NodeType>
int NodePriorityQueue<IntType, VectorType, NodeType>::compare(int a, int b)
{
	return m_comparer.compare(m_queue[a].first, m_queue[b].first, m_queue[a].second, m_queue[b].second);
}

template <typename IntType, typename VectorType, typename NodeType>
void NodePriorityQueue<IntType, VectorType, NodeType>::swap(int a, int b)
{
	std::pair<IntType, VectorType> temp = m_queue[a];
	m_queue[a] = m_queue[b];
	m_queue[b] = temp;
}

template <typename IntType, typename VectorType, typename NodeType>
int NodePriorityQueue<IntType, VectorType, NodeType>::push(IntType index, VectorType vector, std::vector<std::vector<NodeType>> nodes)
{
	int a = m_queue.size();
	int b;

	std::pair<IntType, VectorType> pair = std::make_pair<IntType, VectorType>((int)index, (Vector)vector);
	m_queue.push_back(pair);
	m_comparer.update(nodes);

	while (true)
	{
		if (a == 0)
			break;
		b = (a - 1);
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

template<typename IntType, typename VectorType, typename NodeType>
std::pair<IntType, VectorType> NodePriorityQueue<IntType, VectorType, NodeType>::pop()
{
	std::pair<IntType, VectorType> result = m_queue[0];
	int a = 0;
	int b;
	int c;
	int d;

	m_queue.erase(m_queue.begin());

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

template<typename IntType, typename VectorType, typename NodeType>
void NodePriorityQueue<IntType, VectorType, NodeType>::clear()
{
	m_queue.clear();
}

template<typename IntType, typename VectorType, typename NodeType>
int NodePriorityQueue<IntType, VectorType, NodeType>::count()
{
	return m_queue.size();
}

template<typename IntType, typename VectorType, typename NodeType>
inline std::vector<std::pair<IntType, VectorType>> NodePriorityQueue<IntType, VectorType, NodeType>::getQueue()
{
	return m_queue;
}

#endif // !NODE_PRIORITY_QUEUE_H