#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>

class Component
{
public:
	inline std::string getId() { return m_id; };

protected:
	std::string m_id;
};
#endif // !COMPONENT_H