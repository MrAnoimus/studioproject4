#include "GameStateManager.h"
//#include "introstate.h"
#include "PlayState.h"
#include <iostream>
#include <time.h>
extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

CPlayState CPlayState::thePlayState;
using namespace std;

void CPlayState::changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
	{
		h = 1;
	}
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

	width = w;
	height = h;
}
void CPlayState::MouseMove(int x , int y)
{
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;
	mouseInfo.lastX = x;
	mouseInfo.lastY = y;

	//check if mouse pointer is inside the button boundaries
	for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
	{
		(*it)->UpdateMouseMove(x,y);
	}

	//to check where camera pan
	if(theCamera->canPan == true)
	{
		//stop making it one line.
		if(mouseInfo.lastX >= width - 50)
		{
			theCamera->isPanRight = true;
		}else
		{
			theCamera->isPanRight = false;
		}
		if(mouseInfo.lastX <= 50)
		{
			theCamera->isPanLeft = true;
		}else
		{
			theCamera->isPanLeft = false;
		}
		if(mouseInfo.lastY <= height-50)
		{
			theCamera->isPanUp = true;
		}else
		{
			theCamera->isPanUp = false;
		}
		if(mouseInfo.lastY >= 50)
		{
			theCamera->isPanDown = true;
		}else
		{
			theCamera->isPanDown = false;
		}
	}
}
void CPlayState::MouseClick(int button , int state , int x , int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		{
			for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
			{
				Citizen *Citizens = *it;
				if (Citizens->active == true&&Citizens->Movedout==true)
				{
					if(myTile[SelectorY][SelectorX].myHouse.GetOwner() == Citizens->GetName())
					{
						Citizens->RenderMood=true;
					}
					else
					{
						Citizens->RenderMood=false;
					}
							
				}
			}
			if (!mouseInfo.mLButtonUp)
			{
				for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
				{
					if ((*it)->buttonhover)
						(*it)->buttonclicked = true;
				}
			}
			else
			{
				for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
				{
					if ((*it)->buttonhover)
						(*it)->buttonclicked = false;
				}
			}

			if (REvent.IsDisplay == false)
			{
				if (state == GLUT_DOWN)
				{
					ClearTileMap();
					mouseInfo.mLButtonUp = state;
					mouseInfo.lastX = x;
					mouseInfo.lastY = y;
				
					
					if(myTile[SelectorY][SelectorX].GetBtype()==1)
					{
						
				
					Astar as(px,py,SelectorX,SelectorY);
				
					bool result = as.Search(Map);
		
					CNode* Node = new CNode;
					Node->x = SelectorX;
					Node->y = SelectorY;
					as.AddCloseList(Node);

				
					if(result)
					{
						moving = true;

						for(int i=0;i<(int)as.closeList.size();i++)
						{
							//Citizen stuff
							CNode* TheNode = new CNode();
							TheNode->x = as.closeList[i]->x*100;
							TheNode->y = as.closeList[i]->y*100;
							cout <<"Size: " <<(int)as.closeList.size() <<std::endl;
							for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
							{
								int j= (int)as.closeList.size();
								Citizen *Citizens = *it;
								if (Citizens->active == true&&Citizens->Movedout==false)
								{
									if(i+1>=j)
									{
										Citizens->CitizenDestination->DestinationList.push_back(TheNode);
										myTile[SelectorY][SelectorX].myHouse.SetOwner(Citizens->GetName());
										Citizens->Movedout=true;
										break;
									}
									if(i>=1)
									{				
										Citizens->CitizenDestination->DestinationList.push_back(TheNode);
										break;
									}
									
									/*if((Citizens->GetPosition().x != as.closeList[i]->x*100)&&(Citizens->GetPosition().y != as.closeList[i]->y*100))
									{
										myTile[SelectorY][SelectorX].myHouse.SetOwner(Citizens->GetName());
									}*/
									
								}
							}
							}
						}
				}
					//check mode
					if(myTile[SelectorY][SelectorX].GetModeOn() == true)
					{
						//only if tile is not clicked on)
						if(myTile[SelectorY][SelectorX].IsClickedOn() == false)
						{
							myTile[SelectorY][SelectorX].SetIsClickedOn(true);
							//reset gaugebar
							myTile[SelectorY][SelectorX].myGaugeBar.setDone(false);
							myTile[SelectorY][SelectorX].myGaugeBar.setPercentage(0);
						}
						//clicked on
						if(myTile[SelectorY][SelectorX].IsClickedOn())
						{
							if(myTile[SelectorY][SelectorX].GetBtype() == 0)
							{
								myTile[SelectorY][SelectorX].SetEmpty(true);
								myTile[SelectorY][SelectorX].SetIsClickedOn(false);
								Map[SelectorY][SelectorX]=10;
							}
							if(myTile[SelectorY][SelectorX].GetBtype() == 1)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myHouse.GetCost());
								Map[SelectorY][SelectorX]=1;
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 2)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myFCourt.GetCost());
								Map[SelectorY][SelectorX]=2;
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 3)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myFCourt.GetCost());
								Map[SelectorY][SelectorX]=3;
							}
							for(int y = 0; y < ROWS; y += 1)
							{
								for(int x = 0; x < COLS; x += 1)
								{
									if(myTile[SelectorY][SelectorX].GetBtype() == 5)
									{
										//once selected and click on set tile to not empty
										myTile[y][x].SetEmpty(false);
										//resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myFCourt.GetCost());
										Map[SelectorY][SelectorX]=10;
									}
									
								}
							}
						}
					}
					if(mouseLC == NULL)
					{
						mouseLC = theSoundEngine->play2D ("SFX/LMBdown.wav", false, true);
					}else
					{
						mouseLC == NULL;
						mouseLC = theSoundEngine->play2D ("SFX/LMBdown.wav", false, true);
					}
					if(mouseLC->getIsPaused() == true)
					{
						mouseLC->setIsPaused(false);
					}
					else if(mouseLC->isFinished() == true)
					{
						mouseLC = NULL;
					}

				}else
				{
					//cout << "LMB is up" << endl;
					if(mouseLC == NULL)
					{
						mouseLC = theSoundEngine->play2D ("SFX/LMBup.wav", false, true);
					}else
					{
						mouseLC == NULL;
						mouseLC = theSoundEngine->play2D ("SFX/LMBup.wav", false, true);
					}
					if(mouseLC->getIsPaused() == true)
					{
						mouseLC->setIsPaused(false);
					}
					else if(mouseLC->isFinished() == true)
					{
						mouseLC = NULL;
					}
				}
			}break;
		}
		case GLUT_RIGHT_BUTTON:
		{
			mouseInfo.mRButtonUp = state;
			if(state == GLUT_DOWN)
			{
				if(myTile[SelectorY][SelectorX].GetModeOn() == false)
				{
					if(theCamera->GetPosition().z >=-500)
					{
						theCamera->isZoomOut = true;
						if(mouseLC == NULL)
						{
							mouseLC = theSoundEngine->play2D ("SFX/zoomout.wav", false, true);
						}else
						{
							mouseLC == NULL;
							mouseLC = theSoundEngine->play2D ("SFX/zoomout.wav", false, true);
						}
					}
					if(theCamera->GetPosition().z <=-725)
					{
						theCamera->isZoomIn = true;
						if(mouseLC == NULL)
						{
							mouseLC = theSoundEngine->play2D ("SFX/zoomin.wav", false, true);
						}else
						{
							mouseLC == NULL;
							mouseLC = theSoundEngine->play2D ("SFX/zoomin.wav", false, true);
						}
					}
				}else
				{
					if(myTile[SelectorY][SelectorX].IsClickedOn() == true)
					{
						myTile[SelectorY][SelectorX].SetIsClickedOn(false);
						//reset gaugebar
						myTile[SelectorY][SelectorX].myGaugeBar.setDone(false);
						myTile[SelectorY][SelectorX].myGaugeBar.setPercentage(0);
					}
					//clicked on
					if(myTile[SelectorY][SelectorX].IsClickedOn() == false)
					{
						if(myTile[SelectorY][SelectorX].GetBtype() == 1)
						{
							myTile[SelectorY][SelectorX].SetEmpty(false);
							Map[SelectorY][SelectorX]=219;
						}
						if(myTile[SelectorY][SelectorX].GetBtype() == 2)
						{
							myTile[SelectorY][SelectorX].SetEmpty(false);
							Map[SelectorY][SelectorX]=219;
						}
						if(myTile[SelectorY][SelectorX].GetBtype() == 3)
						{
							myTile[SelectorY][SelectorX].SetEmpty(false);
							Map[SelectorY][SelectorX]=219;
						}
					}
				}
			}
		}break;
		case GLUT_MIDDLE_BUTTON:
		{
			if(state == GLUT_DOWN)
			{
			
			}break;
		}
	}
}
void CPlayState::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;
	//keyboard input
	if(myKeys[27]==true)
	{
		exit(0);
	}
	if(REvent.IsDisplay == false)
	{
		if(myKeys['1']==true)
		{
			if(myTile[SelectorY][SelectorX].GetBtype()==0)
			{
				myTile[SelectorY][SelectorX].SetBtype(1);
			}else
			{
				myTile[SelectorY][SelectorX].SetBtype(0);
			}
		}
		if(myKeys['2']==true)
		{
			if(myTile[SelectorY][SelectorX].GetBtype()==0)
			{
				myTile[SelectorY][SelectorX].SetBtype(2);
			}else
			{
				myTile[SelectorY][SelectorX].SetBtype(0);
			}
		}
		if(myKeys['3']==true)
		{
			if(myTile[SelectorY][SelectorX].GetBtype()==0)
			{
				myTile[SelectorY][SelectorX].SetBtype(3);
			}else
			{
				myTile[SelectorY][SelectorX].SetBtype(0);
			}
		}
		if(myKeys['w']==true)
		{
			TheChoice->SetPopup(true);
		}

		if(myKeys['m'] == true)
		{
			minigameobjects->minigame = true;
			//theCamera->canPan = !theCamera->canPan;
		}
		if(myKeys['s'] == true)
		{
			theCamera->canPan = !theCamera->canPan;
		}
		if(myKeys['n'] == true)
		{
		}

		if(myKeys['p'] == true)
		{
			for(int y = 0; y < ROWS; y += 1)
			{
				for(int x = 0; x < COLS; x += 1)
				{
					myTile[y][x].SetModeOn(!myTile[y][x].GetModeOn());
				}
			}
		}

		if(myKeys['k'] == true)
		{
			ofstream fout("LuaScript/save2.txt");
			//minigame = false;
			if(fout.is_open())
			{
				cout <<endl;
				cout << "File Opened successfully!!!. Writing data from array to file" << endl;
				for(int y = 0; y < ROWS; y ++ )
				{
					for(int x = 0; x < COLS; x ++ )
					{
						fout << Map[y][x]<<" ";
						cout <<Map[y][x]<<",";
					}
				}
			}
			fout.close();
		}

		if(myKeys['l'] == true)
		{
			cout <<endl;
			for(int y = 0; y < ROWS; y ++ )
			{
				for(int x = 0; x < COLS; x ++ )
				{
					cout<<Map[y][x]<<",";
				}
			}
		}
	}
}

void CPlayState::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
}

bool CPlayState::Init()
{
	//getting the initial array
	width = glutGet(GLUT_SCREEN_WIDTH);
	height = glutGet(GLUT_SCREEN_HEIGHT);
	typeS = 0;
	moving = false;
	movingX = false;
	myGameUI.Init();
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

	//sets the player resources;
	lua_getglobal(L2,"FOOD");
	int food = lua_tointeger(L2,2);
	resource.SetFood(food);

	lua_getglobal(L2,"MONEY");
	float money= (float)lua_tonumber(L2,3);
	resource.SetMoney(money);

	lua_getglobal(L2, "MANPOWER");
	int manpower = lua_tointeger(L2,4);
	resource.SetManpower(manpower);

	lua_getglobal(L2,"CITIZEN");
	int numOfCitizen= lua_tointeger(L2,5);
	resource.SetCitizen(numOfCitizen);

	std::cout <<"FOOD: "<< resource.GetFood() << std::endl;
	std::cout << "Money: "<<resource.GetMoney() << std::endl;
	std::cout <<"ManPower: "<< resource.GetManPower() << std::endl;
	std::cout << "Citizen: "<<resource.GetCitizen() << std::endl;

	lua_close(L2);

	//camera data and init
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 400, 300, -500.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );
	angle = 0.0f;
	frequency = 30.0f;
	//data used for testing 
	//
	//load texture here
	LoadTGA(&BackgroundTexture,"Textures/Farmbg.tga");
	LoadTGA(&MenuTexture[0],"Textures/redbg.tga");
	LoadTGA(&MenuTexture[1],"Textures/greenbg.tga");
	LoadTGA(&EventTexture[0],"Textures/bad1.tga");
	LoadTGA(&EventTexture[1],"Textures/bad2.tga");
	LoadTGA(&EventTexture[5],"Textures/good1.tga");
	LoadTGA(&EventTexture[6],"Textures/good2.tga");
	LoadTGA(&EventTexture[7],"Textures/good3.tga");

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

	//Sound Engine init
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine)
	{
		return false;
	}
	theSoundEngine->setSoundVolume(volume);
	//Choice stuff
	TheChoice = new Choices;

	//end of choice

	for(int i =0; i< resource.GetCitizen(); i++)
	{
		Citizen *go;
		go = FetchObject();
		go->active = true;
		go->Movedout=false;
		go->SetPosition(Vector3D(100,100,0));
	}
	//mg init
	minigameobjects = new MiniGame();
	minigameobjects->Init(theCamera);

	LoadTGA(&minigameobjects->MGTexture[0],"Textures/mgbg.tga");
	LoadTGA(&minigameobjects->MGTexture[1],"Textures/coinsprite.tga");
	LoadTGA(&minigameobjects->MGTexture[2],"Textures/catchersprite.tga");
	LoadTGA(&minigameobjects->MGTexture[3],"Textures/hgsprite.tga");
	LoadTGA(&minigameobjects->MGTexture[4],"Textures/mgframe.tga");

	//minigame buttons init
	returnbutton = new ButtonClass();
	LoadTGA(&returnbutton->button[0],"Textures/returnup.tga");
	LoadTGA(&returnbutton->button[1],"Textures/returndown.tga");
	returnbutton->Set(360,460,230,260);
	ListofButtons.push_back(returnbutton);

	//load ttf fonts
	minigameobjects->mgfont.init("Fonts/GretoonHighlight.TTF", 72);

	OKbutton = new ButtonClass();
	LoadTGA(&OKbutton->button[0],"Textures/okup.tga");
	LoadTGA(&OKbutton->button[1],"Textures/okdown.tga");
	OKbutton->Set(240,580,400,460);
	ListofButtons.push_back(OKbutton);

	//Day progress
	day = 1;
	Dtimer = 0;
	return true;
}

void CPlayState::Cleanup()
{
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

	if(minigameobjects->minigame)
	{
		GameObject* catcher2 = (GameObject*)minigameobjects->catcher;
		if(catcher2->active)
		{
			if(catcher2->type == GameObject::GO_CATCHER)
			{
				if(myKeys['a'] == true)
				{
					minigameobjects->mgctr2++; 
					minigameobjects->inverted = true;
					catcher2->pos.x += 2;
				}
				if(myKeys['d'] == true)
				{
					minigameobjects->mgctr2++;
					minigameobjects->inverted = false;
					catcher2->pos.x -= 2;
				}
			}
		}
	}
}
void CPlayState::Update(CGameStateManager* theGSM) 
{
	//cout << width << ", " << height << endl;

	if(minigameobjects->minigame)
	{
		theCamera->canPan = false;
		theCamera->isZoomIn = false;
		theCamera->isZoomOut = false;
	}

	if(minigameobjects->addcash)
	{
		resource.SetMoney(resource.GetMoney() + minigameobjects->cash);
		minigameobjects->addcash = false;
	}

	if(returnbutton->buttonclicked)
	{
		minigameobjects->minigame = false;
		mouseInfo.mLButtonUp = false;
	}

	if (sizechanged)
		{
			OKbutton->Set(240,580,400,460);
			returnbutton->Set(360,460,230,260);
			sizechanged = false;
		}

		if(OKbutton->buttonclicked)
		{
			theCamera->canPan = true;
			REvent.IsDisplay = false;
			mouseInfo.mLButtonUp = false;
			OKbutton->buttonclicked = false;
		}

	if (REvent.IsDisplay ==false)
	{
		//Time progression
		if(Dtimer < 302)
		{
			//Dtimer++;
			
			/*if (Dtimer >= 300)
			{
				day +=1;
				REvent.IsDisplay = true;
				REvent.Random();
				REvent.CreateEventz(REvent.type);
				cout <<REvent.type<<endl;
				theCamera->canPan = false;
				Dtimer = 0;
			}*/
		}
		//
		//myGameUI.Update();
		//tile selection check
		int offsetX;
		int offsetY;
		offsetX =(width/8);
		offsetY = (height/6);
		if(mouseInfo.lastX > (width/2))
		{
			SelectorX = ((-mouseInfo.lastX + width-(offsetX/4))/ offsetX);
			SelectorX = ((-mouseInfo.lastX + width-(offsetX/4))/ offsetX);
		}else
		{
			SelectorX = ((-mouseInfo.lastX + width+(offsetX/4))/ offsetX);
		}
		if(mouseInfo.lastY > (height/2))
		{
			SelectorY =((-mouseInfo.lastY + height-(offsetY/4))/ offsetY);
		}else
		{
			SelectorY = ((-mouseInfo.lastY + height+(offsetY/4))/ offsetY);
		}
		//////
		for(int y = 0; y < ROWS; y += 1)
		{
			for(int x = 0; x < COLS; x += 1)
			{
				if(SelectorX != x && SelectorY != y)
				{
					myTile[y][x].SetIsSelected(false);
				}else
				{
					if(myTile[y][x].IsSelected())
					{
						myTile[y][x].SetIsSelected(false);
					}
					myTile[SelectorY][SelectorX].SetIsSelected(true);
				}//!clean up sometime later watch out list
				if(	myTile[y][x].GetModeOn() == true)
				{
					myTile[y][x].Update();
				}else
				{	
					if(myTile[y][x].IsClickedOn() == false)
					{
						myTile[y][x].SetBtype(0);
					}
					myTile[y][x].Update();
				}
			}
		}
		for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
		{
			Citizen *Citizens = *it;
			if (Citizens->active == true)
			{
				Citizens->MoodUpdate();
				px = Citizens->GetPosition().x*0.01f;
				py = Citizens->GetPosition().y*0.01f;
				//Citizens->Position.x++;
				if(myTile[SelectorY][SelectorX].GetModeOn()==false)
				{
					if(Citizens->CitizenDestination->DestinationList.size()>=1)
					{
						if(Citizens->Movedout==true)
						{
							Vector3D position;
							position.x = Citizens->CitizenDestination->DestinationList[Citizens->index]->x;
							position.y = Citizens->CitizenDestination->DestinationList[Citizens->index]->y;
							position.z = Citizens->GetPosition().z;
							if ((position -Citizens->GetPosition()).LengthSquared() > (0))
							{
								Vector3D direction(position - Citizens->GetPosition());
								Citizens->Position.x += direction.Normalized().x;
								Citizens->Position.y += direction.Normalized().y;
							}
							if(Citizens->GetPosition().x== position.x && Citizens->GetPosition().y == position.y)
							{
								if(Citizens->index < Citizens->CitizenDestination->DestinationList.size()-1)
								{
								Citizens->index++;
								}
							}
							
						}
					}
				}
			}	
		}
		if(minigameobjects->minigame)
		{
			minigameobjects->Update();
		}

	}
}

void CPlayState::DrawTileContent()
{
	for(int y = 0; y < ROWS; y += 1)
	{
		for(int x = 0; x < COLS; x += 1)
		{
			//myTile[y][x].SetIsClickedOn(true);
			if(Map[y][x] == 219)
			{//3 = UNBUILDABLE
				myTile[y][x].SetType(4);
				myTile[y][x].SetBtype(5);
			}
			if(Map[y][x] == 1)
			{//
				myTile[y][x].SetBtype(1);
			}

			if(Map[y][x] == 2)
			{
				myTile[y][x].SetBtype(2);
			}
			if(Map[y][x] == 3)
			{//
				myTile[y][x].SetBtype(3);
			}
			if(Map[y][x] == 4)
			{
				myTile[y][x].SetBtype(4);
			}
			if(Map[y][x] == 10)
			{
				myTile[y][x].SetType(0);//tile color code
			}
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
	
	minigameobjects->theCamera = theCamera;

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
	glDisable(GL_TEXTURE_2D);

	if(minigameobjects->minigame)
	{
		//if(minigameobjects->timer <= 0)
		//{
				
		//}
		glTranslatef(0,0,-10);
		minigameobjects->Draw();
	}	

	DrawTileContent();
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{	
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			Citizens->Draw();
		}
	}
	//Enable 2D text display and HUD
	theCamera->SetHUD( true);
	myGameUI.Draw(0,height - 50);
	print(our_font,0,height-100,"type: %d",myTile[SelectorY][SelectorX].GetBtype());
	print(our_font,0,height-300,"OwnerName: %s",myTile[SelectorY][SelectorX].myHouse.GetOwner().c_str());
	/*print(our_font,0,height-300,"Day: %d\n", day);
	print(our_font,0,height-400,"Timer: %d\n", Dtimer);*/
	print(our_font,0,height-500,"Cash: %f\n", resource.GetMoney());
	//for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	//{	
	//	Citizen *Citizens = *it;
	//	if (Citizens->active == true)
	//	{
	//		//Citizens->MoodUpdate(Citizen::EATINGPLACE, Citizen::FOOD);
	//		//print(our_font,0,height-500,"MouseX: %s",Citizens->GetName().c_str());
	//	}
	//}
	RenderUI();
	if(minigameobjects->minigame)
	{
		if(minigameobjects->timer <= 0)
		{
			returnbutton->Render();
		}
	}
	TheChoice->Draw();
	if(REvent.IsDisplay == true)
	{
		HandleREvents(REvent.type);
		glPushMatrix();
			OKbutton->Render();
		glPopMatrix();
	}
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}

void CPlayState::RenderUI(void)
{
	//print(our_font,0,250,"Current Money :%.2f\nCurrent Manpower :%1i\nCurrent Citizen:%1i",PlayerResource.GetMoney() ,PlayerResource.GetManPower(),PlayerResource.GetCitizen());
	if(minigameobjects->minigame)
	{
		glPushMatrix();
			glColor3f(1,0,0);
			print(minigameobjects->mgfont,width/2,height*0.8,"%d\n", minigameobjects->timer);
			glColor3f(1,1,1);
		glPopMatrix();
		glPushMatrix();
			glScalef(0.2,0.2,0.2);
			glColor3f(0,0,0);
			print(minigameobjects->mgfont,width*0.40,height*0.75,"Cash: %f\n", minigameobjects->cash);
			glColor3f(1,1,1);
		glPopMatrix();
	}
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
	int a = CitizenList.size();
	stringstream ss;
	ss << a;
	std::string str = go->GetName() + ss.str();
	go->SetName(str);
	CitizenList.push_back(go);
	return go;
}

void CPlayState::HandleREvents(int type)
{
	switch (type)
	{
		// - money
	case 0:
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[0].id);
			glPushMatrix();
				glTranslatef(100,50,0);
				glScalef(0.75,0.75,0.75);
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
		break;
	case 1:
		// - money
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[1].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
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
		break;
	case 2:
		// + money
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[5].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
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
		break;
	case 3:	
		// + Man power
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[6].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
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
		break;
	case 4:
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[7].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
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
		break;
	}
	
}

void CPlayState::ClearTileMap(void)
{
	for(int y = 0;y<ROWS;y+=1)
	{
		for(int x = 0;x<COLS;x+=1)
		{
			if(myTile[y][x].GetBtype()!=1&&myTile[y][x].GetBtype()!=2&&myTile[y][x].GetBtype()!=3&&myTile[y][x].GetBtype()!=0)
			{
				if(Map[y][x] != 1&&Map[y][x] != 2&&Map[y][x] != 3&&Map[y][x] != 219)
				{
					Map[y][x] = 10;
				}
			}
			if(Map[y][x]==11)
			{
				Map[y][x]=10;
			}
		}
	}
}