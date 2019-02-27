#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Vector/Vector.h"
#include <string>

class Node
{
public:
	Node();

	// getters and setters
	int getHeuristic();
	void setHeuristic(int h);
	int getEstimate();
	void setEstimate(int e);
	std::shared_ptr<Node> getParent();
	void setParent(std::shared_ptr<Node> parent);
	Vector getParentIndex();
	void setParentIndex(Vector parentIndex);
	int getJumpValue();
	void setJumpValue(int value);
	int getStatus();
	void setStatus(int status);

	short m_G; // ??

private:
	std::shared_ptr<Node> m_parent; // parent node that we got to his node from
	Vector m_parentIndex; // used to get the parent in neighbours list
	int m_weight; // weight of the node
	int m_heuristic; // F - a star hueristic
	int m_estimate;
	int m_status; // nodes open / closed status
	int m_jumpValue; // the current jump distance of the node
};
#endif // !NODE_H

