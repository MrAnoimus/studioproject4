#include "Resource.h"


CResource::CResource(void)
{


}

CResource::~CResource(void)
{
}

int CResource::NumOfFood = 100;
int CResource::NumOfMoney = 100.0f;
int	CResource::NumOfManPower = 100;
int	CResource::NumOfCitizen = 100;

int CResource::GetFood(void)
{
	return  NumOfFood;
}

int CResource::GetManPower()
{
	return NumOfManPower;
}

int CResource::GetMoney()
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

void CResource::SetMoney(int NewMoney)
{
	NumOfMoney = NewMoney;
}