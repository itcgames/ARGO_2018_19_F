#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <functional>
#include <stack>

template <typename Data, typename Container, typename Predicate>
class NodePriorityQueue : public std::priority_queue<Data, Container, typename Predicate>
{
public:
	std::vector<class T> m_queue;
	void compare();
	void swap();
	void update();
	void pop();
	void first();
	void clear();
};

#endif // !PRIORITY_QUEUE_H
