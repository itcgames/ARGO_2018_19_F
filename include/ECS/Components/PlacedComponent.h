#pragma once
#include "c:\Users\gameuser\Documents\ARGO_2018_19_F\include\ECS\Components\Component.h"
class PlacedComponent :
	public Component
{
public:
	PlacedComponent();
	~PlacedComponent();

	void setPlaced();
	bool getPlaced();

private:

	bool m_placed = false;
};

