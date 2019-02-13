#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

//  Project.
#include "ECS/Components/Component.h"
#include "SDL.h"
#include "Vector/Vector.h"

class AnimationComponent : public Component
{
public:
	AnimationComponent(Vector& first, Vector& last);

	Vector& getCurrentFrame();
	Vector& getLastFrame();
	Vector& getFirstFrame();
	double getFrameTime();

	void setCurrentFrame(Vector& frame);
	void setLastFrame(Vector& frame);
	void setFirstFrame(Vector& frame);
	void setFrameTime(double time);

	SDL_RendererFlip m_flip = SDL_FLIP_NONE;
	SDL_Point m_centre = { 0,0 };
	float m_angle = 0.0f;

private:
	Vector m_currentFrame;
	Vector m_firstFrame;
	Vector m_lastFrame;
	double m_frameTime;

};
#endif // !ANIMATION_COMPONENT_H

