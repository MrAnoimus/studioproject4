#include "Building.h"


Building::Building(void)
: Size(50),Cost(100.0f)
{
	this->Cost = 100.0f;
}

Building::~Building(void)
{
	
}
//getter
float Building::GetBPercentage()
{
	return this->BuildPercentage;
}
int Building::GetSize()
{
	return this->Size;
}
float Building::GetCost()
{
	return this->Cost;
}
Vector3D Building::GetPosition()
{
	return this->Position;
}
//setter
void Building::SetBPercentage(float pc)
{
	this->BuildPercentage = pc;
}
void Building::SetSize(int size)
{
	this->Size = size;
}
void Building::SetPosition(Vector3D pos)
{
	this->Position = pos;
}