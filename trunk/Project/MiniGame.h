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

	void DrawMGBG();
	void DrawTextureBase();
	void DrawTextureBaseNotInvert();
	void DrawTextureBaseInvert();
	void DrawObject(GameObject *mg, const GLuint Texture);

	TextureImage coin;

	//minigame stuffs
	bool minigame;
	float speed;
	int CposX;
	int CposY;
	Vector3D gravity;
	float fallspeed;
	int spawntime;

	int mgctr, mgctr2;
	bool inverted;

};

