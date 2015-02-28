#include "GameStateManager.h"
//#include "introstate.h"
#include "PlayState.h"
#include <iostream>
#include <time.h>
#include "ResultState.h"
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
						//
						Astar as(px,py,SelectorX,SelectorY);
						//
						bool result = as.Search(Map);
						//
						CNode* Node = new CNode;
						Node->x = SelectorX;
						Node->y = SelectorY;
						//
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
										Citizens->owner = Citizens->GetName();
										Citizens->SetPlace(myTile[SelectorY][SelectorX-1].Tag, 0);
										Citizens->SetPlace(myTile[SelectorY][SelectorX+1].Tag, 1);
										Citizens->SetPlace(myTile[SelectorY-1][SelectorX].Tag, 2);
										Citizens->SetPlace(myTile[SelectorY+1][SelectorX].Tag, 3);
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
								//myTile[SelectorY][SelectorX].Tag ="nothing";
							}
							if(myTile[SelectorY][SelectorX].GetBtype() == 1)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myHouse.GetCost());
								Map[SelectorY][SelectorX]=1;
								myTile[SelectorY][SelectorX].Tag ="house";
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 2)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myFCourt.GetCost());
								Map[SelectorY][SelectorX]=2;
								myTile[SelectorY][SelectorX].Tag ="eatingplace";
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 3)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myGstore.GetCost());
								Map[SelectorY][SelectorX]=3;
								myTile[SelectorY][SelectorX].Tag ="workplace";
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
										//myTile[y][x].Tag = "nothing";
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
			if(myTile[SelectorY][SelectorX].GetModeOn())
			{
				if(myTile[SelectorY][SelectorX].GetBtype()==0)
				{
					myTile[SelectorY][SelectorX].SetBtype(1);
				}else
				{
					myTile[SelectorY][SelectorX].SetBtype(0);
				}
			}
			
		}
		if(myKeys['2']==true)
		{
			if(myTile[SelectorY][SelectorX].GetModeOn())
			{
				if(myTile[SelectorY][SelectorX].GetBtype()==0)
				{
					myTile[SelectorY][SelectorX].SetBtype(2);
				}else
				{
					myTile[SelectorY][SelectorX].SetBtype(0);
				}
			}
		}
		if(myKeys['3']==true)
		{
			if(myTile[SelectorY][SelectorX].GetModeOn())
			{
				if(myTile[SelectorY][SelectorX].GetBtype()==0)
				{
					myTile[SelectorY][SelectorX].SetBtype(3);
				}else
				{
					myTile[SelectorY][SelectorX].SetBtype(0);
				}
			}
		}
		if(myKeys['w']==true)
		{
			TheChoice->SetPopup(true);
		}
		if(myKeys['m'] == true)
		{
			minigameobjects->minigame = true;
			minigameobjects->playing = true;
		}
		if(myKeys['s'] == true)
		{
			theCamera->canPan = !theCamera->canPan;
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
			theCamera->canPan = !theCamera->canPan;
			for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
			{
				Citizen *Citizens = *it;
				Citizens->RenderMood=false;
				
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
	//lua_getglobal(L2,"FOOD");
	//int food = lua_tointeger(L2,2);
	//resource.SetFood(food);

	//lua_getglobal(L2,"MONEY");
	//float money= (float)lua_tonumber(L2,3);
	//resource.SetMoney(money);

	//lua_getglobal(L2, "MANPOWER");
	//int manpower = lua_tointeger(L2,4);
	//resource.SetManpower(manpower);

	//lua_getglobal(L2,"CITIZEN");
	//int numOfCitizen= lua_tointeger(L2,5);
	//resource.SetCitizen(numOfCitizen);

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
	LoadTGA(&ResultTexture[0],"Textures/WinScreen.tga");
	LoadTGA(&ResultTexture[1],"Textures/LosingScreen.tga");
	

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
	if (!theSoundEngine){return false;}

	mouseLC = NULL;
	playBGM = NULL;

	if(playBGM == NULL)
	{
		playBGM = theSoundEngine->play2D ("SFX/playbgm.mp3", false, true);
	}else
	{
		playBGM == NULL;
		playBGM = theSoundEngine->play2D ("SFX/playbgm.mp3", false, true);
	}
	if(playBGM->getIsPaused() == true)
	{
		playBGM->setIsPaused(false);
	}
	else if(playBGM->isFinished() == true)
	{
		playBGM = NULL;
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

		//srand((unsigned int)deltaTime);
		//srand((unsigned int)deltaTime);
		srand((unsigned int)i);
		Random = rand()%3+1;
		Random2 = Random;
		cout <<"Random "<<Random<<endl;
		cout <<"Random2 "<<Random2<<endl;
		if(Random == Random2)
		{
			srand((unsigned int)i*i);
			Random = rand()%3+1;
		}
		
		cout <<"After Random "<<Random<<endl;
		cout <<"After Random2 "<<Random2<<endl;
		
		if(Random==1)
		{
			go->SetFavourite(Citizen::FOOD);
		}
		else if(Random==2)
		{
			go->SetFavourite(Citizen::SLACK);
		}
		else if(Random==3)
		{
			go->SetFavourite(Citizen::WORK);
		}
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
	OKbutton->Set(350,450,400,460);
	ListofButtons.push_back(OKbutton);

	Choice1 = new ButtonClass();
	LoadTGA(&Choice1->button[0],"Textures/CheapTree.tga");
	LoadTGA(&Choice1->button[1],"Textures/CheapTree.tga");
	Choice1->Set(100,300,460,500);
	ListofButtons.push_back(Choice1);

	Choice2 = new ButtonClass();
	LoadTGA(&Choice2->button[0],"Textures/ExpensiveTree.tga");
	LoadTGA(&Choice2->button[1],"Textures/ExpensiveTree.tga");
	Choice2->Set(500,700,460,500);
	ListofButtons.push_back(Choice2);
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
	if(myKeys['r'] == true)
	{
		resource.SetWin(0);
		theGSM->ChangeState( CResultState::Instance() );
	}
	static int lastTime = GetTickCount();
	++frameCount;
	int time = GetTickCount();
	deltaTime = (time - lastTime) / 1000.f;
	if(myKeys['t'] == true)
	{
		resource.SetWin(1);
		theGSM->ChangeState( CResultState::Instance() );
	}
	if (myGameUI.myGameTime.daycheck == true)
	{

		REvent.IsDisplay = true;
		REvent.Random();
		REvent.CreateEventz(REvent.type);
		theCamera->canPan = false;
		myGameUI.myGameTime.daycheck = false;
	}
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
		Choice1->Set(300,520,460,520);
		Choice2->Set(350,450,520,580);
		sizechanged = false;
	}
	if(OKbutton->buttonclicked)
	{
		theCamera->canPan = true;
		REvent.IsDisplay = false;
		mouseInfo.mLButtonUp = false;
		OKbutton->buttonclicked = false;
	}
	if(Choice1->buttonclicked)
	{ 
		TheChoice->popup = false;
		mouseInfo.mLButtonUp = false;
		Choice1->buttonclicked = false;
	}
	if(Choice2->buttonclicked)
	{
		TheChoice->popup = false;
		mouseInfo.mLButtonUp = false;
		Choice2->buttonclicked = false;
	}
	
	if (REvent.IsDisplay ==false)
	{
		
		myGameUI.Update();
		//tile selection check
		
		if(myTile[SelectorY][SelectorX].GetModeOn())
		{
			int offsetX;
			int offsetY;

			offsetX =(width/8);
			offsetY = (height/6);
			if(mouseInfo.lastX > (width/2))
			{
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
		}
		
		if(SelectorX >7)
		{
			SelectorX = 7;
		}
		if(SelectorX <1)
		{
			SelectorX =0;
		}
		if(SelectorY > 5)
		{
			SelectorY =5;
		}
		if(SelectorY<0)
		{
			SelectorY =0;
		}
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
							if(Citizens->MovedBack==false)
							{
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
							else
							{
								if ((position -Citizens->GetPosition()).LengthSquared() > (0))
								{
									Vector3D direction(position - Citizens->GetPosition());
									Citizens->Position.x += direction.Normalized().x;
									Citizens->Position.y += direction.Normalized().y;
								}
								if(Citizens->GetPosition().x== position.x && Citizens->GetPosition().y == position.y)
								{
									if(Citizens->index > 0)
									{
										Citizens->index--;
									}
									else
									{
										Citizens->MovedBack=false;
										Citizens->Movedout=false;
									}
								}
							}

						}
					}
				}
				for(int y = 0; y < ROWS; y += 1)
				{
					for(int x = 0; x < COLS; x += 1)
					{
						if(myTile[y][x].GetPosition().x+50>=Citizens->GetPosition().x
							&&myTile[y][x].GetPosition().x-50<=Citizens->GetPosition().x
							&&myTile[y][x].GetPosition().y+50>=Citizens->GetPosition().y
							&&myTile[y][x].GetPosition().y-50<=Citizens->GetPosition().y)
						{
							if(myTile[y][x].GetEmpty()==true)
							{
								if(myTile[y][x].myHouse.GetOwner()==Citizens->GetName())
								{
									Citizens->MovedBack=true;
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
	
		for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
		{
			Citizen *Citizens = *it;
			if (Citizens->active == true)
			{	
				if(myTile[SelectorY][SelectorX].myHouse.GetOwner()==Citizens->GetName())
				{
					Citizens->RenderMood=true;
					
				}
				else
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
			if(Map[y][x] == 219)
			{//3 = UNBUILDABLE
				myTile[y][x].SetType(4);
				myTile[y][x].SetBtype(5);
			}
			if(Map[y][x] == 1)
			{//
				myTile[y][x].SetBtype(1);
				myTile[y][x].Tag = "house";
			}
			if(Map[y][x] == 2)
			{
				myTile[y][x].SetBtype(2);
				myTile[y][x].Tag = "eatingplace";
			}
			if(Map[y][x] == 3)
			{//
				myTile[y][x].SetBtype(3);
				myTile[y][x].Tag = "workplace";
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
		glTranslatef(0,0,-10);
		minigameobjects->Draw();
	}	
	DrawTileContent();
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{	
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			Citizens->Draw(SelectorX*100, SelectorY*100);
		}
	}
	//Enable 2D text display and HUD
	theCamera->SetHUD( true);
	
	myGameUI.Draw(0,height - 50);
	myGameUI.DrawSelect(750,50,myTile[SelectorY][SelectorX].GetModeOn(),myTile[SelectorY][SelectorX].GetBtype());
	myGameUI.DrawResource(725,130);
	myGameUI.DrawResourceData(width-200,height-310,resource.GetMoney(),100,100);
	print(our_font,0,250,"PickX :%d PickY:%d",SelectorX,SelectorY);
	RenderUI();
	if(minigameobjects->minigame)
	{
		if(minigameobjects->timer <= 0)
		{
			returnbutton->Render();
		}
	}
	if(REvent.IsDisplay == true)
	{
		REvent.HandleREvents(REvent.type);
		glPushMatrix();
			OKbutton->Render();
		glPopMatrix();
	}
	if(TheChoice->popup ==true)
	{
		glPushMatrix();
		 TheChoice->Draw(1);
		  Choice1->Render();
		  Choice2->Render();
		glPopMatrix();
	}
	/*if(resource.GetMoney() <=0)
	{
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, ResultTexture[1].id);
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
	}*/
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
			print(minigameobjects->mgfont,width*0.40,height*0.75,"Cash: %d\n", minigameobjects->cash);
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
			
			int Random = (rand() % 3 + 1);	
			if(Random==1)
			{
				go->SetFavourite(Citizen::FOOD);
			}
			else if(Random==2)
			{
				go->SetFavourite(Citizen::SLACK);
			}
			else if(Random==3)
			{
				go->SetFavourite(Citizen::WORK);
			}
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
