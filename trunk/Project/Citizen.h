#include <iostream>
#include <string>
#include "LoadTGA.h"
//#include "TextureImage.h"
#pragma once

using namespace std;
class Citizen
{

public:
	bool active;
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
	TextureImage Moody;
	
	void MoodUpdate( 
		NearByBuilding TheBuildings,
		Favourite TheFavourite);
	std::string GetMood();
	Citizen(void);
	~Citizen(void);
	void Draw(void);
private:
	bool happy;
	float HappinessLevels;
	Favourite TheFavourites;
	Mood TheMoods;
	NearByBuilding TheBuildings;
};

