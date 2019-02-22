#ifndef CHARACTER_CONTROL_SYSTEM_H
#define CHARACTER_CONTROL_SYSTEM_H
//  Standard.
#include <map>
//  Project.
#include "ECS/Systems/System.h"
#include "Vector/Vector.h"
#include "States/IdleState.h"
#include "ECS/Components/ControllerComponent.h"
#include "ECS/Components/PhysicsComponent.h"
#include "ECS/Components/GraphicsComponent.h"
#include "ECS/Components/PositionComponent.h"
#include "ECS/Components/CollisionComponent.h"
#include <SDL_mixer.h>

class CharacterControlSystem : public System
{
public:
	CharacterControlSystem();
	virtual void update(double dt) override;

	PlayerState* m_state = new IdleState();

	const int CROUCH_HEIGHT = 80;
	const int STAND_HEIGHT  = 96;

	Mix_Chunk * m_jumpSound;
};
#endif // !CHARACTER_CONTROL_SYSTEM_H