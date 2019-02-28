#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Vector/Vector.h"
#include <string>

class Node
{
public:
	Node(Vector location, int index);

	// getters and setters
	void setStart(bool start);
	bool getStart();

	void setGoal(bool start);
	bool getGoal();

	bool getShouldJump();
	void setShouldJump(bool jump);

	void setVisited(bool visited);
	bool getVisited();

	bool getGoBack();
	void setGoBack(bool status);

	Vector& getLocation();
	void setLocation(Vector location);

	std::shared_ptr<Node> getNext();
	void setNext(std::shared_ptr<Node> next);

	std::shared_ptr<Node> getPrevious();
	void setPrevious(std::shared_ptr<Node> previous);

private:
	std::shared_ptr<Node> m_next; // m_next
	std::shared_ptr<Node> m_previous; // previous node
	Vector m_location;
	int m_index;
	bool m_visited;
	bool m_start;
	bool m_goal;
	bool m_goBack; // visited
	bool m_shouldJump;
};
#endif // !NODE_H

