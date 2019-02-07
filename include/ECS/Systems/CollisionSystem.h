#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include "ECS/Components/PhysicsComponent.h"

class CollisionSystem : public System
{
public:
	virtual void update(double dt) override;
private:
	inline float checkSign(float num)
	{
		float result = 0;
		if (num > 0)
		{
			result = 1;
		}
		if (num < 0)
		{
			result = -1;
		}

		return result;
	};

};
#endif // !COLLISION_SYSTEM_H
