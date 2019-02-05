#include "Components/PositionComponent.h"

/// <summary>
/// Constructor - set the ID for the component and initialize vector
/// </summary>
PositionComponent::PositionComponent()
{
	id = "POSITION";
	m_position = new Vector();
}

/// <summary>
/// Constructor with arugments - pass vector to initialize component with a vector position
/// </summary>
/// <param name="v">vector arguement to initialize position</param>
PositionComponent::PositionComponent(Vector& v)
{
	id = "POSITION";
	m_position = new Vector(v);
}

/// <summary>
/// Setter - update the component value
/// </summary>
/// <param name="v">vector arguement - update the current position with this value</param>
void PositionComponent::setPos(Vector& v)
{
	m_position = &v;
}

/// <summary>
/// Getter - return the component value
/// </summary>
/// <returns>vector pointer for component</returns>
Vector* PositionComponent::getPos()
{
	return m_position;
}

