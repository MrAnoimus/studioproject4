#include <iostream>
#include <string>
#include <stdlib.h>
#include "LoadTGA.h"
#include <time.h>
#include "vector3D.h"
#include "FreeType.h"
#include "Camera.h"
#include "Human.h"
#include <string>
#include "Destination.h"

#pragma once

using namespace std;
class Citizen: public Human
{

public:
	int index;
	Destination* CitizenDestination;
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
		NOTHING,
		HOUSES
	};

	
	TextureImage Happy;
	TextureImage Sad;
	TextureImage Enraged;
	TextureImage Okay;

	void MoodUpdate();
	std::string GetMood();
	Citizen(void);
	~Citizen(void);
	void Draw(void);

	void SetFavourite(Favourite MyFavourites);
	void SetPlace(std::string tag, int number);
	
	std::string GetFavourites(void);
	std::string GetPlace(int i);

	void RenderCitizen();

	TextureImage FemaleCitizen;
	TextureImage MaleCitizen;
	TextureImage StatsBG;
	int AnimationCounter;
	bool AnimationInvert;

	void DrawSquare(float xSize, float ySize);

	void SetAnimationCounter(int AnimationCounter);
	int GetAnimationCounter(void);
	
	

	bool RenderMood;

	void StatsBoard(void);

	void DrawInGameText(std::string Text);

	void SetName(std::string Name);

	std::string GetName(void);

	bool Movedout;
	bool MovedBack;std::string owner;
private:
	
	
	int dir;
	
	int Gender;
	bool happy;
	float HappinessLevels;
	Favourite TheFavourites;
	Mood TheMoods;
	NearByBuilding TheBuildings[4];

	std::string Name;
};

