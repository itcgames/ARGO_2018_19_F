#ifndef NODE_PRIORITY_QUEUE_H
#define NODE_PRIORITY_QUEUE_H

#include "AI/NodeComparer.h"
#include <queue>
#include <vector>
#include <functional>
#include <stack>

template <typename NodeType>
class NodePriorityQueue : public std::priority_queue<NodeType>
{
public:
	NodePriorityQueue();
	NodePriorityQueue(NodeComparer<NodeType>* comparer);

	int compare(Vector& a, Vector& b);
	void swap(int a, int b);
	int push(std::weak_ptr<NodeType> i);
	std::weak_ptr<NodeType> pop();
	void clear();
	int count();

private:
	std::vector<std::vector<std::shared_ptr<Node>>> m_queue;
	NodeComparer* m_comparer;
};

#endif // !NODE_PRIORITY_QUEUE_H