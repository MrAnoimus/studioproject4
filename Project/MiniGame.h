#pragma once
#include "LoadTGA.h"
#include <time.h>
#include "GameObject.h"
#include "MyMath.h"

using namespace std;

class MiniGame
{
private:
	

public:
	MiniGame(void);
	~MiniGame(void);

	void Update();

	int AnimationCounter;

	void SetAnimationCounter(int AnimationCounter);
	int GetAnimationCounter(void);
	void RenderCoin();

	void DrawMGBG();
	void DrawTextureBase();
	void DrawObject(GameObject *mg);

	TextureImage coin;

	//minigame stuffs
	bool minigame;	
	GameObject ghost;
	float speed;
	int CposX;
	int CposY;
	Vector3D gravity;
	float fallspeed;
	int spawntime;

};

