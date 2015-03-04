#include "GameStateManager.h"
//#include "gamestate.h"
#include "PlayState.h"
#include "introstate.h"
#include <mmsystem.h>
#include "SettingState.h"
#include "PlayState.h"
#include "CreditState.h"

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

CIntroState CIntroState::theIntroState;

void CIntroState::changeSize(int w, int h)
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
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}
void CIntroState::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;
	cout<<"Key: "<<key<<" STATE : " <<myKeys[key]<<endl;
}

void CIntroState::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
	cout<<"Key: "<<key<<" STATE : " <<myKeys[key]<<endl;
}
void CIntroState::MouseMove(int x , int y)
{
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;

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
	
	if(!start)
	{
		//check if mouse pointer is inside the button boundaries
		for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
			(*it)->UpdateMouseMove(x,y);

		if(startbutton->buttonhover)
		{
			hoverStart = true;
		}
		else
		{
			hoverStart = false;
		}

		if(contbutton->buttonhover)
		{
			hoverCont = true;
		}
		else
		{
			hoverCont = false;
		}

		if(settingsbutton->buttonhover)
		{
			hoverSet = true;
		}
		else
		{
			hoverSet = false;
		}

		if(exitbutton->buttonhover)
		{
			hoverExit = true;
		}
		else
		{
			hoverExit = false;
		}

		if(hoverStart)
		{	
			if(menuGUIstart == NULL)
				{menuGUIstart = theSoundEngine->play2D ("SFX/misc_menu.wav", false, true);}		
			/*else{menuGUIstart == NULL;
				 menuGUIstart = theSoundEngine->play2D ("SFX/misc_menu.wav", false, true);}*/
			if(menuGUIstart->getIsPaused() == true){menuGUIstart->setIsPaused(false);}
			else if(menuGUIstart->isFinished() == true){menuGUIstart = NULL;}
		}

		if(hoverCont)
		{	
			if(menuGUIcont == NULL)
			{
				menuGUIcont = theSoundEngine->play2D ("SFX/misc_menu_2.wav", false, true);
			}		
			/*else{menuGUIcont == NULL;
				 menuGUIcont = theSoundEngine->play2D ("SFX/misc_menu_2.wav", false, true);}*/
			if(menuGUIcont->getIsPaused() == true)
			{
				menuGUIcont->setIsPaused(false);
			}
			/*else if(menuGUIcont->isFinished() == true)
			{
				menuGUIcont = NULL;
			}*/
		}

		if(hoverSet)
		{
			if(menuGUIset == NULL)
				{menuGUIset = theSoundEngine->play2D ("SFX/misc_menu_3.wav", false, true);}		
			/*else{menuGUIset == NULL;
				 menuGUIset = theSoundEngine->play2D ("SFX/misc_menu_3.wav", false, true);}*/
			if(menuGUIset->getIsPaused() == true){menuGUIset->setIsPaused(false);}
			else if(menuGUIset->isFinished() == true){menuGUIset = NULL;}
		}

		if(hoverExit)
		{
			if(menuGUIexit == NULL)
				{menuGUIexit = theSoundEngine->play2D ("SFX/misc_menu_4.wav", false, true);}		
			/*else{menuGUIexit == NULL;
				 menuGUIexit = theSoundEngine->play2D ("SFX/misc_menu_4.wav", false, true);}*/
			if(menuGUIexit->getIsPaused() == true){menuGUIexit->setIsPaused(false);}
			else if(menuGUIexit->isFinished() == true){menuGUIexit = NULL;}
		}
	}
}
void CIntroState::MouseClick(int button , int state , int x , int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		{

			mouseInfo.mLButtonUp = state;
			
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;
			if(!loading || !loading2)
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
			}
		}break;
		case GLUT_RIGHT_BUTTON:
		{

		}break;
		case GLUT_MIDDLE_BUTTON:
		{

		}break;
	}
}
bool CIntroState::Init()
{
	cout << "CIntroState::Init\n" << endl;

	lua_State *L2 = lua_open();
	luaL_openlibs(L2);
	if (luaL_loadfile(L2, "LuaScript/setting.lua") || lua_pcall(L2, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L2, -1));
		return -1;
	}
	lua_getglobal(L2,"VOLUME");
	double VOLUME = lua_tonumber(L2, 1);
	volume =  VOLUME;
	
	lua_close(L2);

	
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );

	LoadTGA(&BackgroundTexture,"Textures/bgtest.tga");
	LoadTGA(&LoadingTexture,"Textures/loading.tga");
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
	//mouseInfo.lastX = glutGet(GLUT_WINDOW_WIDTH) >> 1;
	//mouseInfo.lastY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;

	//Sound Engine init
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine){return false;}
	theSoundEngine->setSoundVolume(volume);

	if(introBGM == NULL)
	{
		introBGM = theSoundEngine->play2D ("SFX/introbgm.mp3", false, true);
	}else
	{
		introBGM == NULL;
		introBGM = theSoundEngine->play2D ("SFX/introbgm.mp3", false, true);
	}
	if(introBGM->getIsPaused() == true)
	{
		introBGM->setIsPaused(false);
	}
	else if(introBGM->isFinished() == true)
	{
		introBGM = NULL;
	}


	menuGUIstart = NULL;
	menuGUIcont = NULL;
	menuGUIset = NULL;
	menuGUIexit = NULL;
	introBGM = NULL;

	hoverStart = false;
	hoverSet = false;
	hoverExit = false;
	hoverCont = false;

	startbutton = new ButtonClass();
	LoadTGA(&startbutton->button[0],"Textures/startup.tga");
	LoadTGA(&startbutton->button[1],"Textures/startdown.tga");
	startbutton->Set(240,580,340,400);
	ListofButtons.push_back(startbutton);

	
	contbutton = new ButtonClass();
	LoadTGA(&contbutton->button[0],"Textures/continueup.tga");
	LoadTGA(&contbutton->button[1],"Textures/continuedown.tga");
	contbutton->Set(300,520,400,460);
	ListofButtons.push_back(contbutton);

	settingsbutton = new ButtonClass();
	LoadTGA(&settingsbutton->button[0],"Textures/settingsup.tga");
	LoadTGA(&settingsbutton->button[1],"Textures/settingsdown.tga");
	settingsbutton->Set(300,520,460,520);
	ListofButtons.push_back(settingsbutton);

	exitbutton = new ButtonClass();
	LoadTGA(&exitbutton->button[0],"Textures/exitup.tga");
	LoadTGA(&exitbutton->button[1],"Textures/exitdown.tga");
	exitbutton->Set(350,450,520,580);
	ListofButtons.push_back(exitbutton);
	loading = false;
	loading2 = false;
	start = false;
	value = 0;
	creditbutton = new ButtonClass();
	LoadTGA(&creditbutton->button[0],"Textures/creditup.tga");
	LoadTGA(&creditbutton->button[1],"Textures/creditdown.tga");
	creditbutton->Set(25,75,520,580);
	ListofButtons.push_back(creditbutton);

	return true;
}
void CIntroState::Cleanup()
{
	//cout << "CIntroState::Cleanup\n" << endl;
	//Delete sound engine
	if (theSoundEngine != NULL){theSoundEngine->drop();}

	if (!ListofButtons.empty()){ListofButtons.clear();}

}

void CIntroState::Pause()
{
	//cout << "CIntroState::Pause\n" << endl;
}

void CIntroState::Resume()
{
	//cout << "CIntroState::Resume\n" << endl;
}

void CIntroState::HandleEvents(CGameStateManager* theGSM)
{
	if (mouseInfo.mLButtonUp) 
	{

	}
	if(myKeys[27]==true)
	{
		exit(0);
	}
	if(myKeys['w'] == true)
	{
		theGSM->ChangeState( CCreditState::Instance() );
	}
}

void CIntroState::Update(CGameStateManager* theGSM)
{
	width = glutGet(GLUT_SCREEN_WIDTH);
	height = glutGet(GLUT_SCREEN_HEIGHT);
	if (sizechanged)
	{
		startbutton->Set(240,580,340,400);
		contbutton->Set(300,520,400,460);
		settingsbutton->Set(300,520,460,520);
		exitbutton->Set(350,450,520,580);
		creditbutton->Set(25,75,520,580);
		sizechanged = false;
	}

	if(startbutton->buttonclicked)
	{
		loading = true;
		/*resource.SetLoad(0);
		theGSM->ChangeState( CPlayState::Instance() );
		mouseInfo.mLButtonUp = false;*/
	}
	if(contbutton->buttonclicked)
	{
		loading2 = true;
		/*resource.SetLoad(1);
		theGSM->ChangeState( CPlayState::Instance() );	
		mouseInfo.mLButtonUp = false;*/
	}
	if(loading == true || loading2 == true)
	{
		value++;
	}
	if(value>100)
	{
		start = true;
		//value=0;
	}
	if(start)
	{
		if(loading)
		{
			resource.SetLoad(0);
			theGSM->ChangeState( CPlayState::Instance() );
			mouseInfo.mLButtonUp = false;
		}
		if(loading2)
		{
			resource.SetLoad(1);
			theGSM->ChangeState( CPlayState::Instance() );	
			mouseInfo.mLButtonUp = false;
		}
		
	}
	if(settingsbutton->buttonclicked)
	{
		theGSM->ChangeState( CSettingState::Instance() );
		mouseInfo.mLButtonUp = false;
	}
	if(creditbutton->buttonclicked)
	{
		theGSM->ChangeState( CCreditState::Instance() );
		mouseInfo.mLButtonUp = false;
	}

	if(exitbutton->buttonclicked)
	{
		exit(0);
	}
	//cout << "CIntroState::Update\n" << endl;
	//MouseMove(mouseInfo.lastX,mouseInfo.lastY);
	//std::cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<std::endl;
}

void CIntroState::Draw(CGameStateManager* theGSM) 
{
	//cout << "CIntroState::Draw\n" << endl;
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

	// Draw Background image
	if(loading || loading2)
	{
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture (GL_TEXTURE_2D, LoadingTexture.id);
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
		//Sleep(1000);
		glDisable(GL_TEXTURE_2D);
	}else
	{
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, BackgroundTexture.id);
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
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			startbutton->Render();
		glPopMatrix();

		glPushMatrix();
			settingsbutton->Render();
		glPushMatrix();

		glPushMatrix();
			exitbutton->Render();
		glPushMatrix();

		glPushMatrix();
			contbutton->Render();
		glPushMatrix();

		glPushMatrix();
			creditbutton->Render();
		glPushMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	glDisable(GL_TEXTURE_2D);
	//drawFPS();
	
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
void CIntroState::calculateFPS()
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
}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void CIntroState::drawFPS()
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
