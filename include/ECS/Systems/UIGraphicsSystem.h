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
	virtual void render(SDL_Renderer * renderer) override; 
	TTF_Font * m_font;
};
#endif // !UI_GRAPHICS_SYSTEM_H
