#ifndef GRAPHICSSYSTEM_H
#define GRAPHICSSYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"

class GraphicsSystem : public System
{
public:
	virtual void update(double dt) {};
	void render(SDL_Renderer * renderer);
};

#endif // !GRAPHICSSYSTEM_H
