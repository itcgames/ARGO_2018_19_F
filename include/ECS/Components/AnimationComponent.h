#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "ECS/Components/Component.h"
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

private:
	Vector m_currentFrame;
	Vector m_firstFrame;
	Vector m_lastFrame;
	double m_frameTime;
};
#endif // !ANIMATION_COMPONENT_H

