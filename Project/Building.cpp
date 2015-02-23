#include "Building.h"


Building::Building(void)
: Size(50),Cost(0)
{
}

Building::~Building(void)
{
	
}
//getter
int Building::GetTier()
{
	return this->Tier;
}

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
void Building::SetTier(int t)
{
	this->Tier = t;
}
void Building::SetCost(float c)
{
	this->Cost = c;
}
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