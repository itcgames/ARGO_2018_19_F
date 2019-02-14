#ifndef UI_CONTROL_SYSTEM_H
#define UI_CONTROL_SYSTEM_H

#include "ECS/Systems/System.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/TextComponent.h"
#include "ECS/Components/AnimationComponent.h"

class UIControlSystem : public System
{
public:
	virtual void update(double dt) override;
	void render(SDL_Renderer * renderer);
};

#endif // !UI_CONTROL_SYSTEM_H

