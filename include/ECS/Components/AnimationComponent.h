#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "ECS/Components/Component.h"
#include "Vector/Vector.h"

class AnimationComponent : public Component
{
public:
	AnimationComponent(Vector* first, Vector* last);

	void setCurrentFrame(Vector& frame);
	void setFrameTime(double time);

	Vector* getCurrentFrame();
	Vector* getLastFrame();
	Vector* getFirstFrame();
	double getFrameTime();

private:
	Vector* m_currentFrame;
	Vector* m_firstFrame;
	Vector* m_lastFrame;
	double m_frameTime;
};
#endif // !ANIMATION_COMPONENT_H

