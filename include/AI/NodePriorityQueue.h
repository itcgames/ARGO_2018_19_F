#ifndef NODE_PRIORITY_QUEUE_H
#define NODE_PRIORITY_QUEUE_H

#include "AI/NodeComparer.h"
#include <queue>
#include <vector>
#include <functional>
#include <stack>

template <typename Data, typename Container, typename Predicate>
class NodePriorityQueue : public std::priority_queue<Data, Container, Predicate>
{
public:
	NodePriorityQueue();
	NodePriorityQueue(NodeComparer<T> comparer);

	int compare(Vector& a, Vector& b);
	void swap(int a, int b);
	void update(T i);
	int push();
	T pop();
	T first();
	void clear();
	int count();
	void remove();

private:
	std::vector<class T> m_queue;
	NodeComparer<T> m_comparer;
};

#endif // !NODE_PRIORITY_QUEUE_H

template<typename Data, typename Container, typename Predicate>
inline NodePriorityQueue<Data, Container, Predicate>::NodePriorityQueue()
{
	m_comparer = NodeComparer<T>.default;
}

template<typename Data, typename Container, typename Predicate>
inline NodePriorityQueue<Data, Container, Predicate>::NodePriorityQueue(NodeComparer<T> comparer)
{
	m_comparer = comparer;
}

template<typename Data, typename Container, typename Predicate>
inline int NodePriorityQueue<Data, Container, Predicate>::compare(Vector& a, Vector& b)
{
	return m_comparer.compare(a,b);
}

template<typename Data, typename Container, typename Predicate>
inline void NodePriorityQueue<Data, Container, Predicate>::swap(int a, int b)
{
	std::vector::swap(a, b);
}

template<typename Data, typename Container, typename Predicate>
inline void NodePriorityQueue<Data, Container, Predicate>::update(T i)
{
	int priorityA = m_queue.length();
	int priorityB;

	m_queue.push_back(i);
	while (true)
	{
		if (priorityA == 0)
		{
			break;
		}
		priorityB
		
	}
}
