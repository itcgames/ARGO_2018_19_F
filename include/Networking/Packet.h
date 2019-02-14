#ifndef PACKAGE_H
#define PACKAGE_H

#include "../../submodules/Vector/Vector.h"
#include <string>

struct Packet
{
	//	General data.
	int playerNum;
	std::string message;
	//	Position data.
	Vector position;
	//	Physics data.
	Vector velocity;
	//	Animation data.
	Vector currentFrame;
	int flipped;
};
#endif // !PACKAGE_H
