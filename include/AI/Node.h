#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Vector/Vector.h"

class Node
{
public:
	Node();

	void setPosition(Vector& pos);
	Vector& getPosition();
	
	void setWeight(float weight);
	float getWeight();

	void addNeighbour(Node* node);
	std::vector<Node*>& getNeighbours();

private:
	Vector m_position;
	float m_weight;
	std::vector<Node*> m_neighbours;
};
#endif // !NODE_H

