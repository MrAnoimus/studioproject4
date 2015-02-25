#pragma once
#include "LoadTGA.h"
#include <time.h>
#include "GameObject.h"
#include "MyMath.h"
#include "Resource.h"

#include "Camera.h"

#include <vector>

//sound
#include <irrKlang.h>
using namespace irrklang;

using namespace std;

const int SPAWN_TIME = 1;
#define MAX_COIN 10
class MiniGame
{
private:

public:
	MiniGame(void);
	~MiniGame(void);

	// The camera
	Camera* theCamera;
	CResource* resource;
	bool Init(Camera* theCamera);
	void Update();

	void Draw();

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

	std::vector<GameObject *> m_goList;
	GameObject* mg;
	GameObject* catcher;

	int spritectime, spriteptime, tctime, tptime, timer;

	//The sound engine vroom vroom
	ISoundEngine* theSoundEngine;
	ISound* mgsfx;

	TextureImage MGBackgroundTexture;
	TextureImage CoinTexture;
	TextureImage CatcherTexture;

};

