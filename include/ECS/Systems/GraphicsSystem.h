#ifndef GRAPHICS_SYSTEM_H
#define GRAPHICS_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/ButtonComponent.h"

class GraphicsSystem : public System
{
public:
	virtual void update(double dt) override;
	void render(SDL_Renderer * renderer);
};
#endif // !GRAPHICS_SYSTEM_H
