#pragma once
#include "LoadTGA.h"
#include <time.h>
#include "GameObject.h"
#include "MyMath.h"
#include "Resource.h"

#include "Camera.h"
#include "ButtonClass.h"

#include "freeType.h"
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
	void DrawTextureBaseHG();

	void DrawObject(GameObject *mg, const GLuint Texture);

	void DrawHourGlass(const GLuint Texture);
	void DrawTimer(const GLuint Texture);


	void CoinPattern1(float posX, float posY, float width);


	//fonts
	freetype::font_data mgfont;

	//minigame stuffs
	bool minigame;
	bool playing;
	float speed;
	int CposX;
	int CposY;
	Vector3D gravity;
	float fallspeed;
	int spawntime;

	bool inverted;

	std::vector<GameObject *> m_goList;
	GameObject* mg;
	GameObject* catcher;

	int cash;
	bool addcash, gamefinish;
	//indexes
	//	coin   catcher hourglass
	int mgctr, mgctr2, mgctr3;

	//sprite delay and real-time based timer
	int spritectime, spriteptime, tctime, tptime, timer;

	//The sound engine vroom vroom
	ISoundEngine* theSoundEngine;
	ISound* mgsfx;

	TextureImage MGTexture[10];

};

