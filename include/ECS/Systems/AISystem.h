#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#include "ECS/Systems/System.h"

class AISystem : public System
{
public:
	AISystem();
	virtual void update(double dt);

private:

};
#endif // !AI_SYSTEM_H

