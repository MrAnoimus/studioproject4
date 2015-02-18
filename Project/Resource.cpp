#include "Resource.h"


CResource::CResource(void)
{
	NumOfFood = 100;
	NumOfMoney = 100.0f;
	NumOfManPower = 100;
	NumOfCitizen = 100;
}


CResource::~CResource(void)
{
}

int CResource::GetFood(void)
{
	return NumOfFood;
}

int CResource::GetManPower()
{
	return NumOfManPower;
}

float CResource::GetMoney()
{
	return NumOfMoney;
}

int CResource::GetCitizen()
{
	return NumOfCitizen;
}

void CResource::SetCitizen(int NewCitizen)
{
	NumOfCitizen = NewCitizen;
}

void CResource::SetFood(int NewFood)
{
	NumOfFood = NewFood;
}

void CResource::SetManpower(int NewManPower)
{
	NumOfManPower = NewManPower;
}

void CResource::SetMoney(float NewMoney)
{
	NumOfMoney = NewMoney;
}