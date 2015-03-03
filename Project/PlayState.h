#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "Astar.h"
#include <mmsystem.h>
#include "GameState.h"
#include "freeType.h"
#include "Citizen.h"
#include "Tile.h"
#include "Choices.h"
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Node.h"

#include "GameTime.h"

//for mini game
#include "GameObject.h"
#include "MyMath.h"
#include "MiniGame.h"
#include <time.h>
//button
#include "ButtonClass.h"
#include "freeType.h"
#include "Definitions.h"
#include "GameUI.h"

//sound
#include <irrKlang.h>
using namespace irrklang;

#include <windows.h>
#include <cstdlib>

//for mini game


// Declare Number Of Rows & Columns For Map Grid
const int ROWS = 6;	
const int COLS = 8;

class CPlayState : public CGameState
{

	//Mouse Info
	typedef struct
	{
		bool mLButtonUp;
		bool mRButtonUp;
		bool middleButtonUp;
		int  lastX, lastY;
	}theMouseInfo;
	public:
		int homeless;
		float ChoiceChance;
		float DestoryedChance;
		int checker;
		int Random;
		int Random2;
		int Map[ROWS][COLS];
		//for choices
		Choices *TheChoice;
		//for movement of citizens to selected tile
		Vector3D Target;
		
		bool moving;
		bool movingX;
		//render ui
		void RenderUI(void);
		float px,py;
		bool Init();
		void Cleanup();

		void Pause();
		void Resume();

		//void HandleREvents(int type);
		void HandleEvents(CGameStateManager* theGSM);
		void Update(CGameStateManager* theGSM);
		//draw function start here
		
		//minigame
		void DrawMGBG();
		//
		void DrawTileContent();
		void Draw(CGameStateManager* theGSM);
		//end of draw function
		void changeSize(int w, int h);
		void MouseMove (int x, int y);
		void MouseClick(int button,int state,int x,int y);
		void KeyboardDown(unsigned char key, int x, int y);
		void KeyboardUp(unsigned char key, int x, int y);
		static CPlayState* Instance()
		{
			return &thePlayState;
		}
		void ClearTileMap();
		
	protected:
		CPlayState()
		:	theCamera(NULL)
		,	minigameobjects(NULL)
		//,	catcher(NULL)
		{ 
		

		}
		~CPlayState()
		{
			if (theCamera != NULL)
			{
				delete theCamera;
				theCamera = NULL;
			}
			if (theSoundEngine != NULL)
			{
				theSoundEngine->drop();
			}
		}
		bool sizechanged;
		float deltaTime;
		int frameCount;
	private:

		static CPlayState thePlayState;
		
		//game ui buttons
		ButtonClass* NormSpeed;
		ButtonClass* MinSpeed;
		ButtonClass* HrSpeed;

		//button
		ButtonClass* OKbutton;
		ButtonClass* Choice1;
		ButtonClass* Choice2;
		ButtonClass* Savebutton;
		//minigame buttons
		ButtonClass* returnbutton;

		//button list
		std::vector<ButtonClass*> ListofButtons;

		// The camera
		Camera* theCamera;
		// Camera
		Vector3D theCameraPosition;
		Vector3D theCameraDirection;
		float angle;
		float frequency;
		//texture
		TextureImage BackgroundTexture;
		TextureImage BGTEST;
		TextureImage MenuTexture[2];
		TextureImage ResultTexture[2];
		
		//keyboard and mouse
		bool myKeys[255];
		theMouseInfo mouseInfo;
		//fonts
		freetype::font_data our_font;

		//The sound engine vroom vroom
		ISoundEngine* theSoundEngine;
		//game sounds
		ISound* mouseLC;
		ISound* playBGM;
		float volume;

		Tile myTile[6][8];
		int SelectorX;
		int SelectorY;
		int housecount;
		int FcourtCount;
		int GstoreCount;
		float TotalEarning;
		void calculateEarning();
		//citizen stuff
		Citizen* FetchObject();
		std::vector<Citizen*> CitizenList;
		
		//minigame stuffs
		MiniGame* minigameobjects;
		/*std::vector<GameObject *> m_goList;
		GameObject* catcher;*/
		//mg time (separate to other times)
		/*int spritectime, spriteptime, tctime, tptime, timer;
		ISound* mgsfx;*/
		float width, height;

		GameUI myGameUI;
		string rNAME;

		void checkUIName();
		std::string Bnames;
		int cost;

		int daypassed;

};
#endif