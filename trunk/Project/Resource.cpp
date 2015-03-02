#include "Resource.h"


CResource::CResource(void)
{


}

CResource::~CResource(void)
{
}

int CResource::NumOfFood = 100;
int CResource::NumOfMoney = 100;
int	CResource::NumOfManPower = 5;
int	CResource::NumOfCitizen = 100;
int	CResource::Win = 0;
int CResource::maxManPower = 10;


void CResource::Update()
{
	if(NumOfManPower<0)
	{
		NumOfManPower=0;
	}
	if(NumOfManPower>maxManPower)
	{
		NumOfManPower = maxManPower;
	}
}

int CResource::GetFood(void)
{
	return  NumOfFood;
}

int CResource::GetWin(void)
{
	return  Win;
}
int CResource::GetMaxManPower()
{
	return maxManPower;
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

void CResource::SetWin(int NewWin)
{
	Win = NewWin;
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