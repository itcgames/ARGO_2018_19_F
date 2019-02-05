#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

class Component
{
public:
	std::string getId() { return m_id; };
	std::string m_id;
};
#endif // !COMPONENT_H