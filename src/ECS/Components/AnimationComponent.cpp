#include "ECS/Components/AnimationComponent.h"

/// <summary>
/// 
/// </summary>
/// <param name="first"></param>
/// <param name="last"></param>
/// <param name="time"></param>
AnimationComponent::AnimationComponent(Vector& first, Vector& last)
{
	m_id = "ANIMATION";
	m_frameTime = 0.0;
	m_currentFrame = first;
	m_firstFrame = first;
	m_lastFrame = last;
}



/// <summary>
/// 
/// </summary>
/// <param name="frame"></param>
void AnimationComponent::setCurrentFrame(Vector& frame)
{
	m_currentFrame = frame;
}



/// <summary>
/// 
/// </summary>
/// <param name="time"></param>
void AnimationComponent::setFrameTime(double time)
{
	m_frameTime = time;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Vector & AnimationComponent::getCurrentFrame()
{
	return m_currentFrame;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Vector & AnimationComponent::getLastFrame()
{
	return m_lastFrame;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
Vector & AnimationComponent::getFirstFrame()
{
	return m_firstFrame;
}



/// <summary>
/// 
/// </summary>
/// <returns></returns>
double AnimationComponent::getFrameTime()
{
	return m_frameTime;
}
