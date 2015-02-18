#include <iostream>
using namespace std;

#include "GameStateManager.h"
//#include "introstate.h"
#include "PlayState.h"


//for random num
#include <time.h>

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

CPlayState CPlayState::thePlayState;

int Map[ROWS][COLS]={
	{219,219,219,219,219,219,219,219},
	{219,'.','.','.','.','.','.',219},
	{219,'.','.','.','.','.','.',219},
	{219,'.','.','.','.','.','.',219},
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
	if(panning == true)
	{
		if(mouseInfo.lastX >= 700){theCamera->isPanRight = true;}
		else{theCamera->isPanRight = false;}
		if(mouseInfo.lastX <= 100){theCamera->isPanLeft = true;}
		else{theCamera->isPanLeft = false;}
		if(mouseInfo.lastY <= 100){theCamera->isPanUp = true;}
		else{theCamera->isPanUp = false;}
		if(mouseInfo.lastY >= 500){theCamera->isPanDown = true;}
		else{theCamera->isPanDown = false;}
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
				//cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<endl;
				//cout<< "LMB is down" <<endl;
				//int randnum = rand()%3;

				if(mouseLC == NULL){mouseLC = theSoundEngine->play2D ("SFX/LMBdown.wav", false, true);}
				else{mouseLC == NULL;
					 mouseLC = theSoundEngine->play2D ("SFX/LMBdown.wav", false, true);}
				if(mouseLC->getIsPaused() == true){mouseLC->setIsPaused(false);}
				else if(mouseLC->isFinished() == true){mouseLC = NULL;}

				testing = true;
				if(myTile[testy][testx].IsSelected())
				{
					Vector3D temp(50+testx*100,50+testy*100,-2);
					mybuilding.SetPosition(temp);
					myTile[testy][testx].SetIsSelected(false);
				}
			}else
			{
				//cout << "LMB is up" << endl;
				if(mouseLC == NULL){
					mouseLC = theSoundEngine->play2D ("SFX/LMBup.wav", false, true);}
				else{mouseLC == NULL;
					 mouseLC = theSoundEngine->play2D ("SFX/LMBup.wav", false, true);}
				if(mouseLC->getIsPaused() == true){mouseLC->setIsPaused(false);}
				else if(mouseLC->isFinished() == true){mouseLC = NULL;}
			
			
				for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					GameObject *go = *it;
					if(!go->active)
					{
						go->active = true;
						go->type = GameObject::GO_COIN;
						go->pos.x = 800 - mouseInfo.lastX + theCamera->GetPosition().x - 400;
						go->pos.y = 600 - mouseInfo.lastY + theCamera->GetPosition().y - 300;
						/*go->pos.z = -2;*/
						//cout << "posX: " << go->pos.x << ", " << "posY: " << go->pos.y << endl;
						break;
					}
				}

			}
		}break;
		case GLUT_RIGHT_BUTTON:
		{
			mouseInfo.mRButtonUp = state;
			if(state == GLUT_DOWN)
			{
				if(theCamera->GetPosition().z >=-500)
				{
					theCamera->isZoomOut = true;
					if(mouseLC == NULL)
					{mouseLC = theSoundEngine->play2D ("SFX/zoomout.wav", false, true);}
					else{mouseLC == NULL;
						mouseLC = theSoundEngine->play2D ("SFX/zoomout.wav", false, true);}
					if(mouseLC->getIsPaused() == true){mouseLC->setIsPaused(false);}
					else if(mouseLC->isFinished() == true){mouseLC = NULL;}
				}
				if(theCamera->GetPosition().z <=-800)
				{
					theCamera->isZoomIn = true;
					if(mouseLC == NULL)
					{mouseLC = theSoundEngine->play2D ("SFX/zoomin.wav", false, true);}
					else{mouseLC == NULL;
						mouseLC = theSoundEngine->play2D ("SFX/zoomin.wav", false, true);}
					if(mouseLC->getIsPaused() == true){mouseLC->setIsPaused(false);}
					else if(mouseLC->isFinished() == true){mouseLC = NULL;}
				}
				//cout << volume;
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
	lua_State *L2 = lua_open();

	luaL_openlibs(L2);
	if (luaL_loadfile(L2, "LuaScript/test.lua") || lua_pcall(L2, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L2, -1));
		return -1;
	}
	lua_getglobal(L2,"VOLUME");
	double VOLUME = lua_tonumber(L2, 1);
	volume =  VOLUME;

	lua_close(L2);

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
	for(int y = 0; y < ROWS; y += 1)
	{
		for(int x = 0; x < COLS; x += 1)
		{
			myTile[y][x].Init();
		}
	}
	//myTile.Init();

	//Sound Engine init
	theSoundEngine = createIrrKlangDevice();
	
	if (!theSoundEngine){return false;}

	theSoundEngine->setSoundVolume(volume);

	Citizen *go;
	go = FetchObject();
	go->active = true;
	CitizenList.push_back(go);

	mybuilding.Init();
	canbuild = true;
	testing = false;


	//for mini game
	panning = true;
	minigame = false;
	gravity.Set(0, -9.8f, 0);
	fallspeed = 1;
	CposX = Math::RandIntMinMax(320, 780);
	CposY = 110;
	spawntime = 0;

	for (int i = 0; i <10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_COIN);
		go->scale.Set(0.5,0.5,0.5);
		m_goList.push_back(go);
		//go->active = true; 
		go->vel.y = -200;
		go->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
		go->pos.y = 600 - Math::RandIntMinMax(110, 310) + theCamera->GetPosition().y - 300;
	}


	return true;
}
void CPlayState::Cleanup()
{
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
	if(myKeys['w']==true)
	{
	}

	if(myKeys['m'] == true)
	{
		/*panning = !panning;
		minigame = !minigame;*/
		panning = false;
		minigame = true;
	}
	
	if(myKeys['n'] == true)
	{
		/*panning = !panning;
		minigame = !minigame;*/
		panning = true;
		minigame = false;
	}
}

void CPlayState::Update(CGameStateManager* theGSM) 
{
	//for mini game
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{
				
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			Citizens->MoodUpdate();
		}
	}

	static int frame = 0;
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	++frame;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float dt = (time - lastTime) / 1000.f;

	lastTime = time;

	spawntime -= dt*0.001;
	if(minigame)
	{
		for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *go = (GameObject *)*it;
			if(go->active)
			{
				go->vel +=  gravity * dt;
				go->pos += fallspeed * (go->vel + (go->vel + gravity * dt)) * 0.5 * dt;

				if(go->pos.y<= (600 - 590 + theCamera->GetPosition().y - 300))
				{
					go->active = false;
					go->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
					go->pos.y = 600 - Math::RandIntMinMax(110, 150) + theCamera->GetPosition().y - 300;
					if(go->vel.y <= -200)
					{go->vel.y = -200;}
				}
			}
			else
			{
				if(spawntime <= 0)
				{
					spawntime = SPAWN_TIME;
					go->active = true;
				}
			}
			cout << "speedfall: " << go->vel.y << endl;
		}
	}


	testx = theCamera->GetPosition().x / 100;
	testy = theCamera->GetPosition().y / 100;
	//std::cout <<"Mouse X: "<< mouseInfo.lastX << std::endl;
	for(int y = 0; y < ROWS; y += 1)
	{
		for(int x = 0; x < COLS; x += 1)
		{
			if(testx != x && testy != y)
			{
				myTile[y][x].SetIsSelected(false);
			}else
			{
				if(myTile[y][x].IsSelected())
				{
					myTile[y][x].SetIsSelected(false);
				}
				myTile[testy][testx].SetIsSelected(true);
			}
			myTile[y][x].Update();
		}
	}
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			Citizens->MoodUpdate();
			if(mouseInfo.lastX<Citizens->GetPosition().x+25&&mouseInfo.lastX>Citizens->GetPosition().x-25)
			{
				Citizens->RenderMood=true;
			}else
			{
				Citizens->RenderMood=false;
			}
		}
	}
}

void CPlayState::DrawTileContent()
{
	for(int y = 0; y < ROWS; y += 1)
	{
		for(int x = 0; x < COLS; x += 1)
		{
			Vector3D temp(50 + x*100,50 +y*100,-1);
			myTile[y][x].SetPosition(temp);
			myTile[y][x].Draw();
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

	//for mini game
	if(minigame)
	{
		glPushMatrix();
		glTranslatef(150,50,-1);
		DrawMGBG();
		
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *go = (GameObject *)*it;
			if (go->active)
			{
				DrawObject(go);
			}
		}
		glPopMatrix();
	} 

	DrawTileContent();
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{
				
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			//Citizens->MoodUpdate(Citizen::EATINGPLACE, Citizen::FOOD);
			Citizens->Draw();
		}
	}
	if(testing)
	{
		mybuilding.Draw();
	}

	// Enable 2D text display and HUD
	theCamera->SetHUD( true);
	print(our_font,0,550,"Cam posX :%f\nCam posY :%f\nCam PosZ:%f",theCamera->GetPosition().x ,theCamera->GetPosition().y,theCamera->GetPosition().z);
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
Citizen* CPlayState::FetchObject()
{
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{
		Citizen *go = *it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}
	Citizen *go = new Citizen();
	go->active = true;
	CitizenList.push_back(go);
	return go;

}

void CPlayState::DrawMGBG()
{
	/*glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
		glColor3f(0.5,0.5,0.5);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,500);
				glTexCoord2f(0,1);
				glVertex2f(500,500);
				glTexCoord2f(0,0);
				glVertex2f(500,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glColor3f(1,1,1);
		/*glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);*/
}

void CPlayState::DrawObject(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_COIN:
		{
			glColor3f(0,0,0);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);
			glutSolidSphere(20,32,32);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
		break;
	case GameObject::GO_CATCHER:
		{
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(go->pos.x, go->pos.y, go->pos.z);
			glScalef(go->scale.x, go->scale.y, go->scale.z);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
		break;
	}
}