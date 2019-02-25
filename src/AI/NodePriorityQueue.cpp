#include "AI/NodePriorityQueue.h"

template<typename NodeType>
NodePriorityQueue<NodeType>::NodePriorityQueue()
{
	m_comparer = NodeComparer();
}

template<typename NodeType>
NodePriorityQueue<NodeType>::NodePriorityQueue(NodeComparer<NodeType>* comparer)
{
	m_comparer = comparer;
}


template<typename NodeType>
int NodePriorityQueue<NodeType>::compare(Vector& a, Vector& b)
{
	return m_comparer.compare(a, b);
}

template<typename NodeType>
void NodePriorityQueue<NodeType>::swap(int a, int b)
{
	std::vector::swap(a, b);
}

template<typename NodeType>
int NodePriorityQueue<NodeType>::push(std::weak_ptr<NodeType> i)
{
	int a = m_queue.size();
	int b;

	m_queue.push(i);
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

template<typename NodeType>
std::weak_ptr<NodeType> NodePriorityQueue<NodeType>::pop()
{
	std::weak_ptr<NodeType> result = m_queue[0];
	int a = 0;
	int b;
	int c;
	int d;

	m_queue[0] = m_queue[m_queue.size() - 1];
	m_queue.erase[m_queue.size() - 1];
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
		if (p == d)
		{
			break;
		}
		swap(a, d);
	}

	return result;
}

template<typename NodeType>
void NodePriorityQueue<NodeType>::clear()
{
	for (std::weak_ptr<NodeType> node : m_queue)
	{
		delete node;
	}

	m_queue.clear();
}

template<typename NodeType>
int NodePriorityQueue<NodeType>::count()
{
	return m_queue.size();
}