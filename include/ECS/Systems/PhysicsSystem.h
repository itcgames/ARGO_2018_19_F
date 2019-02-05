#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "ECS/Systems/System.h"

class PhysicsSystem : public System
{
public:
	void update() override;
private:

};

#endif // !PHYSICSSYSTEM_H
