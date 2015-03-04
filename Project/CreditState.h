#pragma once

#ifndef CREDITSTATE_H
#define CREDITSTATE_H

#include "GameState.h"
#include "freeType.h"
#include "PlayState.h"
#include "freeType.h"
#include "Resource.h"
class CCreditState : public CGameState
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

	static CCreditState* Instance()
	{
		return &theCreditState;
	}

protected:
	CCreditState() :theCamera(NULL)
	{

	}
	~CCreditState()
	{
		if (theCamera != NULL)
		{
			delete theCamera;
			theCamera = NULL;
		}
	}
private:

	static CCreditState theCreditState;
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

	TextureImage BackgroundTexture[2];	

	
	freetype::font_data our_font;
	GLfloat	cnt1;
};

#endif