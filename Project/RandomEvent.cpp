#include "RandomEvent.h"

CRandomEvent::CRandomEvent(void)
{
	IsDisplay = false;
}


CRandomEvent::~CRandomEvent(void)
{
}

int CRandomEvent::Random()
{
	int i = rand()% 5;
	type = i;
	return type;
}

void CRandomEvent::CreateEventz(int typez)
{
	switch (typez)
	{
	case 0:
		{
			resource.SetMoney(resource.GetMoney() -10.5f);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		}
		break;
	case 1:
		{
			resource.SetMoney(resource.GetMoney() -10.5f);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		}

		break;
	case 2:
		{
			resource.SetMoney(resource.GetMoney() +10.5f);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		}
		break;
	case 3:
		{
			resource.SetManpower(resource.GetManPower() +10);
			cout <<"The Amount of Man Power is "<<resource.GetManPower()<<"\n";
		}
		break;
	case 4:
		{
			resource.SetManpower(resource.GetManPower() +10);
			cout <<"The Amount of Man Power is "<<resource.GetManPower()<<"\n";
		}
		break;

	default:
		break;
	}
}