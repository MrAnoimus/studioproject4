#pragma once
#include "vector3D.h"

class Human
{
public:
	Human(void);
	~Human(void);

	Vector3D GetPosition();
	void SetPosition(Vector3D Position);
Vector3D Position;
private:
	
};

