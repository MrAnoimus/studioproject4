#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <mmsystem.h>
#include "GameState.h"
#include "freeType.h"
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
		//
		void DrawQuad(float x , float y,float z,int R,int G, int B , float Alpha);
		//
		void Draw(CGameStateManager* theGSM);

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
		bool LoadTGA(TextureImage *texture, char *filename);
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

};
#endif