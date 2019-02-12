#ifndef PACKAGE_H
#define PACKAGE_H

#include "../submodules/Vector/Vector.h"
#include <string>

struct Packet
{
	int playerNum;
	std::string message;
	Vector position;
};
#endif // !PACKAGE_H
