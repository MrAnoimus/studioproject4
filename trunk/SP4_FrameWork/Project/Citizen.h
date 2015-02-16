#include <iostream>
#include <string>
#pragma once

class Citizen
{

public:
	enum Favourite
	{
		FOOD,
		WORK,
		SLACK
	};
	enum Mood
	{
		HAPPY,
		SAD,
		ENRAGE,
		OKAY
	};
	enum NearByBuilding
	{
		EATINGPLACE,
		WORKPLACE,
		NOTHING
	};
	void MoodUpdate( 
		NearByBuilding TheBuildings,
		Favourite TheFavourite);
	std::string GetMood();
	Citizen(void);
	~Citizen(void);
private:
	bool happy;
	float HappinessLevels;
	Favourite TheFavourites;
	Mood TheMoods;
	NearByBuilding TheBuildings;
};

