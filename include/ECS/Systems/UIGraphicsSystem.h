#ifndef UI_GRAPHICS_SYSTEM_H
#define UI_GRAPHICS_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/TextComponent.h"

class UIGraphicsSystem : public System
{
public:
	virtual void update(double dt) override;
	void render(SDL_Renderer * renderer);
private:
	TTF_Font * m_font = TTF_OpenFont("resources/SHOWG.TTF", 24);
};
#endif // !UI_GRAPHICS_SYSTEM_H
