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
//for mini game
#include "GameObject.h"
#include "MyMath.h"
#include "MiniGame.h"
//sound
#include <irrKlang.h>
using namespace irrklang;



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
		//for choices
		Choices *TheChoice;
		//for movement of citizens to selected tile
		Vector3D Target;
		int index;
		bool moving;
		bool movingX;
		//render ui
		void RenderUI(void);
		float px,py;
		bool Init();
		void Cleanup();

		void Pause();
		void Resume();

		void HandleREvents(int type);
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
		CPlayState()
		:	theCamera(NULL)
		,	minigameobjects(NULL)
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

	private:
		static CPlayState thePlayState;
	
		// The camera
		Camera* theCamera;
		// Camera
		Vector3D theCameraPosition;
		Vector3D theCameraDirection;
		float angle;
		float frequency;
		//texture
		TextureImage BackgroundTexture;
		TextureImage MenuTexture[2];
		TextureImage EventTexture[10];
		//keyboard and mouse
		bool myKeys[255];
		theMouseInfo mouseInfo;
		//fonts
		freetype::font_data our_font;

		//The sound engine vroom vroom
		ISoundEngine* theSoundEngine;
		//game sounds
		ISound* mouseLC;
		float volume;

		Tile myTile[6][8];
		int SelectorX;
		int SelectorY;

		//citizen stuff
		Citizen* FetchObject();
		std::vector<Citizen*> CitizenList;
		
		//minigame stuffs
		MiniGame* minigameobjects;
		MiniGame mgstuffs;
		std::vector<GameObject *> m_goList;

		int typeS;
};
#endif