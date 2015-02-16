#pragma once
#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <iostream>
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output

#include <vector>
#include <GL/glut.h>
#include "vector3D.h"
#include "Camera.h"
#include "TextureImage.h"
//#include "freeType.h"

using namespace std;

class CGameState;

class CGameStateManager
{
	public:
		//void changeSize(int w, int h);
		bool Init(const char* title, int width=1024, int height=760, 
				  int bpp=0, bool fullscreen=false);
		void Cleanup();

		void ChangeState(CGameState* state);
		void PushState(CGameState* state);
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();

		bool Running() { return m_bRunning; }
		void Quit() { m_bRunning = false; }

		CGameState* getActiveState ();

	private:
		// the stack of states
		vector<CGameState*> StackOfStates;

		bool m_bRunning;
		bool m_bFullscreen;
};

#endif