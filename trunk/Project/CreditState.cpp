#include "CreditState.h"
#include "GameStateManager.h"

#include "introstate.h"
#include <mmsystem.h>
#include <iostream>

#include "Definitions.h"
#include "ButtonClass.h"

using namespace std;

CCreditState CCreditState::theCreditState;

void CCreditState::changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);
	sizechanged = true;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,10000);
	glMatrixMode(GL_MODELVIEW);
}

void CCreditState::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;
	cout<<"Key: "<<key<<" STATE : " <<myKeys[key]<<endl;
}

void CCreditState::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
	cout<<"Key: "<<key<<" STATE : " <<myKeys[key]<<endl;
}
void CCreditState::MouseMove(int x , int y)
{
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;

	//check if mouse pointer is inside the button boundaries
	for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
	{
		(*it)->UpdateMouseMove(x,y);
	}
	//Update on y axis
	theCamera->Pitch( diffY * 3.142f / 180.0f );

	////Update on x and z axis
	angle += (float) diffX * 3.142f / 180.0f;
	if (angle > 6.284f)
		angle -= 6.284f;
	else if (angle < -6.284f)
		angle += 6.284f;
	theCamera->Yaw( -angle );

	mouseInfo.lastX = x;
	mouseInfo.lastY = y;
}
void CCreditState::MouseClick(int button , int state , int x , int y)
{
	switch (button)
	{
	
		case GLUT_LEFT_BUTTON:
		{	
			if (!mouseInfo.mLButtonUp)
			{
				for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
				{
					if ((*it)->buttonhover)
					{
						(*it)->buttonclicked = true;
					}
				}
			}

			else
			{
				for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
				{
					if ((*it)->buttonhover)
					{
						(*it)->buttonclicked = false;
					}
				}
			}

			mouseInfo.mLButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;
		}break;
		case GLUT_RIGHT_BUTTON:
		{

		}break;
		case GLUT_MIDDLE_BUTTON:
		{

		}break;
	}
}
bool CCreditState::Init()
{
	sizechanged = false;
	cout << "CCreditState::Init\n" << endl;
	
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );

	LoadTGA(&BackgroundTexture[0],"Textures/credit.tga");
	LoadTGA(&BackgroundTexture[1],"Textures/LosingScreen.tga");

	Returnbutton = new ButtonClass();
	LoadTGA(&Returnbutton->button[0],"Textures/returnup.tga");
	LoadTGA(&Returnbutton->button[1],"Textures/returndown.tga");
	Returnbutton->Set(730,780,5,50); 	
	ListofButtons.push_back(Returnbutton);

	our_font.init("Fonts/FFF_Tusj.TTF", 42);

	//  The number of frames
	frameCount = 0;
	//  Number of frames per second
	fps = 0;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	currentTime = 0, previousTime = 0;

	// realtime loop control
	timelastcall=timeGetTime();
	frequency = 30.0f;
	for(int i=0; i<255; i++)
	{
		myKeys[i] = false;
		//cout<<i<<":"<<myKeys[i]<<endl;
	}
	angle = 0.0f;

	mouseInfo.lastX = 800 >> 1;
	mouseInfo.lastY = 600 >> 1;

	
	

	return true;
}
void CCreditState::Cleanup()
{
	//cout << "CResultState::Cleanup\n" << endl;
}

void CCreditState::Pause()
{
	//cout << "CResultState::Pause\n" << endl;
}

void CCreditState::Resume()
{
	//cout << "CResultState::Resume\n" << endl;
}

void CCreditState::HandleEvents(CGameStateManager* theGSM)
{
	if (mouseInfo.mLButtonUp) 

	{
	

	}
	if(myKeys[27]==true)
	{
		exit(0);
	}
	if(myKeys[13] == true)
	{
		theGSM->ChangeState( CIntroState::Instance() );
	}
}

void CCreditState::Update(CGameStateManager* theGSM)
{
	//cout << "CResultState::Update\n" << endl;
	//MouseMove(mouseInfo.lastX,mouseInfo.lastY);
	//std::cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<std::endl;

	if (sizechanged)
	{
		Returnbutton->Set(730,780,5,50); 	
		sizechanged = false;
	}

	if (Returnbutton->buttonclicked)
	{
		theGSM->ChangeState(CIntroState::Instance());
		Returnbutton->buttonclicked = false;
	}
}

void CCreditState::Draw(CGameStateManager* theGSM) 
{
	//cout << "CResultState::Draw\n" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	theCamera->Update();
	/*this->HandleEvents(theGSM);*/
	if ((timeGetTime()-timelastcall)>1000/frequency)
	{
		// Calculate the framerate
		calculateFPS();
		timelastcall=timeGetTime();
	}
	// Enable 2D text display and HUD
	theCamera->SetHUD( true );

	
	glEnable(GL_TEXTURE_2D);

		// Draw Background image
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, BackgroundTexture[0].id);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0);
					glVertex2f(0,600);
					glTexCoord2f(1,0);
					glVertex2f(800,600);
					glTexCoord2f(1,1);
					glVertex2f(800,0);
					glTexCoord2f(0,1);
					glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
	Returnbutton->Render();

	glDisable(GL_TEXTURE_2D);
	//drawFPS();
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
void CCreditState::calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}

	ButtonClass* returnbutton;
	std::vector<ButtonClass*> ListofButtons;
}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void CCreditState::drawFPS()
{
	//  Load the identity matrix so that FPS string being drawn
	//  won't get animates
	glLoadIdentity ();

	//  Print the FPS to the window
	if (fps > 28.30f)
	{
		glColor3f( 1.0f, 1.0f, 1.0f);
	}
	else if (fps > 28.0f)
	{
		glColor3f( 0.0f, 1.0f, 0.0f);
	}else
	{
		glColor3f( 1.0f, 0.0f, 0.0f);
	}
	print(our_font, 0, 550,"FPS: %4.2f", fps);
	glColor3f( 1.0f, 1.0f, 1.0f);
}
