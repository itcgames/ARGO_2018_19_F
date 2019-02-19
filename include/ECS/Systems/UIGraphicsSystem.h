#ifndef UI_GRAPHICS_SYSTEM_H
#define UI_GRAPHICS_SYSTEM_H

//  Project.
#include "ECS/Systems/System.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/AnimationComponent.h"
#include "ECS/Components/TextComponent.h"
#include "ECS/Components/UIComponent.h"
#include "ECS/Components/ControllerComponent.h"

class UIGraphicsSystem : public System
{
public:
	virtual void update(double dt) override;
	void render(SDL_Renderer * renderer);
	TTF_Font * m_font;
private:
	int m_selected;	//	The number in the order that is selected.
};
#endif // !UI_GRAPHICS_SYSTEM_H
