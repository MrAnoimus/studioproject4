#pragma once

#ifndef RESULTSTATE_H
#define RESULTSTATE_H

#include "GameState.h"
#include "freeType.h"

class CResultState
{
	//Mouse Info
	typedef struct
	{
		bool mLButtonUp;
		bool mRButtonUp;
		bool middleButtonUp;
		int  lastX, lastY;
	}theMouseInfo;

	//texture info
	typedef struct												// Create A Structure
	{
		GLubyte	*imageData;										// Image Data (Up To 32 Bits)
		GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
		GLuint	width;											// Image Width
		GLuint	height;											// Image Height
		GLuint	texID;											// Texture ID Used To Select A Texture
	}TextureImage;

public:

	void changeSize(int w, int h);
		void MouseMove (int x, int y);
		void MouseClick(int button,int state,int x,int y);
		void KeyboardDown(unsigned char key, int x, int y);
		void KeyboardUp(unsigned char key, int x, int y);
		bool Init();
		void Cleanup();
		void renderScene(void);

		void Pause();
		void Resume();

		void HandleEvents(CGameStateManager* theGSM);
		void Update(CGameStateManager* theGSM);
		void input(void);
		void Draw(CGameStateManager* theGSM);

		static CResultState* Instance()
		{
			return &theResultState;
		}

	protected:
		CResultState() :theCamera(NULL)
		{

		}
		~CResultState()
		{
			if (theCamera != NULL)
			{
				delete theCamera;
				theCamera = NULL;
			}
		}
	private:
		static CResultState theResultState;
		bool LoadTGA(TextureImage *texture, char *filename);
		// The camera
		Camera* theCamera;
		// Camera
		Vector3D theCameraPosition;
		Vector3D theCameraDirection;
		float angle;
		//  The number of frames
		int frameCount;
		//  Number of frames per second
		float fps;
		//  currentTime - previousTime is the time elapsed
		//  between every call of the Idle function
		int currentTime, previousTime;
		//  Pointer to a font style..
		//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
		//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
		//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
		//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
		//GLvoid *font_style;
		void *font_style;
		// Calculate the FPS
		void calculateFPS();
		// Display FPS
		void drawFPS();
		//  Draws a string at the specified coordinates.
		void printw (float x, float y, float z, char* format, ...);
		// realtime loop control
		long timelastcall;
		// realtime loop control - frequency
		float frequency;
		bool myKeys[255];
		theMouseInfo mouseInfo;
		TextureImage BackgroundTexture;	

		freetype::font_data our_font;
		GLfloat	cnt1;
};

#endif
