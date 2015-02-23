#include "Human.h"


Human::Human(void)
{
}


Human::~Human(void)
{
}

Vector3D  Human::GetPosition(void)
{
	return this->Position;
}

void Human::SetPosition(Vector3D thisPosition)
{
	Position = thisPosition;
}