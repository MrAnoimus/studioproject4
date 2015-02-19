#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <mmsystem.h>
#include "GameState.h"
#include "freeType.h"
#include "Citizen.h"
#include "Tile.h"
#include "Building.h"

//sound
#include <irrKlang.h>
using namespace irrklang;

//for mini game
#include "GameObject.h"
#include "MyMath.h"
#include "MiniGame.h"

//for mini game
const int SPAWN_TIME = 1;
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
		bool Init();
		void Cleanup();

		void Pause();
		void Resume();

		void HandleEvents(CGameStateManager* theGSM);
		void Update(CGameStateManager* theGSM);
		//draw function start here
		//minigame
		void DrawMGBG();
		void DrawTextureBase();
		void DrawObject(GameObject *go);
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

	protected:
		CPlayState():theCamera(NULL)
		{ 
		}
		~CPlayState()
		{
			if (theCamera != NULL)
			{
				delete theCamera;
				theCamera = NULL;
			}
		}

	private:
		static CPlayState thePlayState;
	
		// The camera
		Camera* theCamera;
		// Camera
		Vector3D theCameraPosition;
		Vector3D theCameraDirection;
		float angle;
		float frequency;

		TextureImage BackgroundTexture;
		bool myKeys[255];
		theMouseInfo mouseInfo;

		freetype::font_data our_font;
		int value;

		//The sound engine vroom vroom
		ISoundEngine* theSoundEngine;
		//game sounds
		ISound* mouseLC;
		float volume;

		Tile myTile[6][8];
		int testx;
		int testy;

		Building mybuilding;
		bool canbuild;
		bool testing;
		//citizen stuff
		Citizen* FetchObject();
		std::vector<Citizen*> CitizenList;
		
		//minigame stuffs
		MiniGame* minigameobjects;
		bool minigame;
		std::vector<GameObject *> m_goList;		
		GameObject ghost;
		float speed;
		int CposX;
		int CposY;
		Vector3D gravity;
		float fallspeed;
		int spawntime;
		

};
#endif