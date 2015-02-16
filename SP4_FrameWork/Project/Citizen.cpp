#include "Citizen.h"


Citizen::Citizen(void)
	:TheMoods(Citizen::SAD)
	,TheFavourites(Citizen::SLACK)
	,TheBuildings(Citizen::NOTHING)
	,happy(false)
	,HappinessLevels(0)
{

}


Citizen::~Citizen(void)
{
}

void Citizen::MoodUpdate(NearByBuilding TheBuilding, Favourite TheFavourite
	)
{
	switch(TheFavourite)
	{
	case Citizen::FOOD:
		if(TheBuilding== Citizen::EATINGPLACE)
		{
			this->happy=true;
		}
		else
		{
			this->happy=false;
		}
		break;
	case Citizen::WORK:
		if(TheBuilding==Citizen::WORKPLACE)
		{
			this->happy=true;
		}
		else
		{
			this->happy=false;
		}
		break;
	case Citizen::SLACK:
		if(TheBuilding==Citizen::NOTHING)
		{
			this->happy=true;
		}
		else
		{
			this->happy=false;
		}
		break;
	default:
		std::cout << "Default" << std::endl;
		break;
	}

	if(this->happy==true)
	{
		if(this->HappinessLevels<=99)
		{
			this->HappinessLevels++;
		}
	}
	else if(this->happy==false)
	{
		if(this->HappinessLevels>=1)
		{
			this->HappinessLevels--;
		}
	}

	if(this->HappinessLevels>0)
	{
		this->TheMoods=Citizen::ENRAGE;
		
	}
	if(this->HappinessLevels>25)
	{
		this->TheMoods=Citizen::SAD;
	}
	if(this->HappinessLevels>50)
	{
		this->TheMoods= Citizen::OKAY;
	}
	if(this->HappinessLevels>75)
	{
		this->TheMoods=Citizen::HAPPY;

	}
	std::cout <<"Happiness Level: " << HappinessLevels << std::endl;
	std::cout <<"TheMood: " << GetMood() << std::endl;
}

std::string Citizen::GetMood(void)
{
	switch(TheMoods)
	{
	case HAPPY:
		return "HAPPY";
		break;
	case SAD:
		return "SAD";
		 break;
	case ENRAGE:
		return "ENRAGE";
		break;
	case OKAY:
		return "OKAY";
		break;
	default:
		return "DEFAULT";
		break;
	}
}