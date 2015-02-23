#include <iostream>
#include <string>
#include "LoadTGA.h"
#include <time.h>
#include "vector3D.h"
#include "FreeType.h"
#include "Camera.h"
#include "Human.h"
#pragma once

using namespace std;
class Citizen: public Human
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
	void SetPlace(NearByBuilding MyBuilding);
	
	std::string GetFavourites(void);
	std::string GetPlace(void);

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


private:
	int dir;
	Vector3D Position;
	int Gender;
	bool happy;
	float HappinessLevels;
	Favourite TheFavourites;
	Mood TheMoods;
	NearByBuilding TheBuildings;
};

