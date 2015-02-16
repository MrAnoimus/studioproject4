#include <iostream>
using namespace std;

#include "GameStateManager.h"
//#include "introstate.h"
#include "PlayState.h"

//for random num
#include <time.h>

CPlayState CPlayState::thePlayState;

int Map[ROWS][COLS]={
	{219,219,219,219,219,219,219,219},
	{219,'.','.','.','.','.','.',219},
	{219,'.','.','.','.','.','.',219},
	{219,219,219,'.',219,219,219,219},
	{219,'.','.','.','.','.','.',219},
	{219,219,219,219,219,219,219,219}
};

void CPlayState::changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}
void CPlayState::MouseMove(int x , int y)
{
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;
	mouseInfo.lastX = x;
	mouseInfo.lastY = y;
	//to check where camera pan
	if(mouseInfo.lastX >= 700)
	{
		theCamera->isPanRight = true;
	}else
	{
		theCamera->isPanRight = false;
	}
	if(mouseInfo.lastX <= 100)
	{
		theCamera->isPanLeft = true;
	}else
	{
		theCamera->isPanLeft = false;
	}
	if(mouseInfo.lastY <= 100)
	{
		theCamera->isPanUp = true;
	}else
	{
		theCamera->isPanUp = false;
	}
	if(mouseInfo.lastY >= 500)
	{
		theCamera->isPanDown = true;
	}else
	{
		theCamera->isPanDown = false;
	}
}
void CPlayState::MouseClick(int button , int state , int x , int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		{
			if (state == GLUT_DOWN)
			{
				mouseInfo.mLButtonUp = state;
				mouseInfo.lastX = x;
				mouseInfo.lastY = y;
				cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<endl;
				cout<< "LMB is down" <<endl;
				//int randnum = rand()%3;

				if(mouseLC == NULL)
				{mouseLC = theSoundEngine->play2D ("SFX/LMBdown.wav", false, true);}
				else{mouseLC == NULL;
					mouseLC = theSoundEngine->play2D ("SFX/LMBdown.wav", false, true);}
				if(mouseLC->getIsPaused() == true){mouseLC->setIsPaused(false);}
				else if(mouseLC->isFinished() == true){mouseLC = NULL;}
			}
			else
			{
				cout << "LMB is up" << endl;
				if(mouseLC == NULL)
				{mouseLC = theSoundEngine->play2D ("SFX/LMBup.wav", false, true);}
				else{mouseLC == NULL;
					mouseLC = theSoundEngine->play2D ("SFX/LMBup.wav", false, true);}
				if(mouseLC->getIsPaused() == true){mouseLC->setIsPaused(false);}
				else if(mouseLC->isFinished() == true){mouseLC = NULL;}
			}
		}

		break;
	case GLUT_RIGHT_BUTTON:
		{
			mouseInfo.mRButtonUp = state;
			if(state == GLUT_DOWN)
			{
				if(theCamera->GetPosition().z >=-500)
				{
					theCamera->isZoomOut = true;
				}
				if(theCamera->GetPosition().z <=-800)
				{
					theCamera->isZoomIn = true;
				}

			}
		}break;
	case GLUT_MIDDLE_BUTTON:
		{

		}break;
	}
}
void CPlayState::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;
}

void CPlayState::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
}

bool CPlayState::Init()
{
	TheCitizen=new Citizen();
	//camera data and init
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 400, 300, -500.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );
	angle = 0.0f;
	frequency = 30.0f;
	//data used for testing 
	value = 0;
	//load texture here
	LoadTGA(&BackgroundTexture,"Textures/Farmbg.tga");
	//load ttf fonts
	our_font.init("Fonts/FFF_Tusj.TTF", 42);
	//init keyboard values
	for(int i=0; i<255; i++)
	{
		myKeys[i] = false;
	}
	//
	myTile.Init();

	//Sound Engine init
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine)
	{
		return false;
	}

	return true;
}
void CPlayState::Cleanup()
{
	//cout << "CMenuState::Cleanup\n" << endl;

	//Delete sound engine
	if (theSoundEngine != NULL)
	{
		theSoundEngine->drop();
	}

}
void CPlayState::Pause()
{
	//cout << "CMenuState::Pause\n" << endl;
}
void CPlayState::Resume()
{
	//cout << "CMenuState::Resume\n" << endl;
}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{
	//keyboard input
	if(myKeys[27]==true)
	{
		exit(0);
	}
	if(myKeys['z'] == true)
	{
		theCamera->SetPosition(theCamera->GetPosition().x,theCamera->GetPosition().y,theCamera->GetPosition().z + 0.1f);
	}
	if(myKeys['x'] == true)
	{
		theCamera->SetPosition(theCamera->GetPosition().x,theCamera->GetPosition().y,theCamera->GetPosition().z - 0.1f);
	}
}

void CPlayState::Update(CGameStateManager* theGSM) 
{
	TheCitizen->MoodUpdate(Citizen::EATINGPLACE,Citizen::FOOD);
}
void CPlayState::DrawTileContent()
{
	for(int y = 0; y < ROWS; y += 1)
	{
		for(int x = 0; x < COLS; x += 1)
		{
			if(Map[y][x] == 'G')
			{
				myTile.Draw(x*100,y*100);
			}
			if(Map[y][x] == 'S')
			{
				myTile.Draw(x*100,y*100);
			}
			if(Map[y][x] == '*')
			{
				myTile.Draw(x*100,y*100);
			}
			if(Map[y][x] == 219)
			{
				myTile.Draw(myTile.GetPosition().x + (x*100),myTile.GetPosition().y+(y*100));
			}
		}
	}
}
void CPlayState::Draw(CGameStateManager* theGSM) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	theCamera->Update();

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture (GL_TEXTURE_2D, BackgroundTexture.id);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,600);
				glTexCoord2f(0,1);
				glVertex2f(800,600);
				glTexCoord2f(0,0);
				glVertex2f(800,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	TheCitizen->Draw();
	DrawTileContent();

	// Enable 2D text display and HUD
	theCamera->SetHUD( true);
	print(our_font,0,550,"Cam posX :%f\nCam posY :%f\nCam PosZ:%f",theCamera->GetPosition().x ,theCamera->GetPosition().y,theCamera->GetPosition().z);
	print(our_font,0,150,"BURDEN");
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
