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
}
void CPlayState::MouseClick(int button , int state , int x , int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
		{
			
		/*	if (REvent.IsDisplay == true)
			{
				if (mouseInfo.lastX >=325 && mouseInfo.lastX <= 475 && mouseInfo.lastY >= 395 && mouseInfo.lastY <=465)
				{
					REvent.IsDisplay = false;
					theCamera->canPan = true;
				}
			}*/

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
				
				for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
				{
					Citizen *Citizens = *it;
					if (Citizens->active == true)
					{
						if(SelectorX==Citizens->GetPosition().x&&SelectorY==Citizens->GetPosition().y)
						{
							Citizens->RenderMood=true;
						}
					}
				}
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

						for(int i=index;i<(int)as.closeList.size();i++)
						{

							for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
							{
								Citizen *Citizens = *it;
								if (Citizens->active == true)
								{
									if((Citizens->GetPosition().x != as.closeList[i]->x*100))
									{
										Citizens->SetPosition(Vector3D(as.closeList[i]->x*100 ,Citizens->GetPosition().y ,Citizens->GetPosition().z));	
									}
									
									if((Citizens->GetPosition().y != as.closeList[i]->y*100))
									{
										Citizens->SetPosition(Vector3D(Citizens->GetPosition().x ,as.closeList[i]->y*100 ,Citizens->GetPosition().z));
									}
									if((Citizens->GetPosition().x != as.closeList[i]->x*100)&&(Citizens->GetPosition().y != as.closeList[i]->y*100))
									{
										myTile[SelectorY][SelectorX].myHouse.SetOwner(Citizens->GetName());
									}
									
								}
							}
							}
						}
				}
				//check mode
				if(myTile[SelectorY][SelectorX].GetModeOn() == true)
				{
					//only if tile is not clicked on)
					if(myTile[SelectorY][SelectorX].IsClickedOn() == false && (resource.GetMoney())>=0)
					{
						myTile[SelectorY][SelectorX].SetIsClickedOn(true);

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
							if(Map[SelectorY][SelectorX] != 1)
							{
								Map[SelectorY][SelectorX]=1;
							}
							
							
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
					}
					if(myTile[SelectorY][SelectorX].IsClickedOn())
					{
						for(int y = 0; y < ROWS; y += 1)
						{
							for(int x = 0; x < COLS; x += 1)
							{	
								if(myTile[y][x].IsClickedOn() == false)
								{
									//set everything else to noting
									myTile[y][x].SetBtype(0);
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
			minigameobjects->minigame = false;
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
	index=0;
	moving = false;
	movingX = false;
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
	LoadTGA(&MGBackgroundTexture,"Textures/mgbg.tga");
	LoadTGA(&CoinTexture,"Textures/coinsprite.tga");
	LoadTGA(&CatcherTexture,"Textures/catchersprite.tga");
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

	//Citizen stuff
	Citizen *go;
	go = FetchObject();
	go->active = true;
	go->SetPosition(Vector3D(101,101,0));
	CitizenList.push_back(go);

	//mg init
	minigameobjects = new MiniGame();

	//mini game coins
	for (int i = 0; i <10; ++i)
	{
		GameObject *mg = new GameObject(GameObject::GO_COIN);
		m_goList.push_back(mg);
		mg->vel.y = -200;
		mg->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
		mg->pos.y = 600 - Math::RandIntMinMax(110, 310) + theCamera->GetPosition().y - 300;
	}
	//mini game catcher
	catcher = new GameObject(GameObject::GO_CATCHER);
	catcher->active = true; 
	catcher->pos.x = 400;
	catcher->pos.y = 50;

	OKbutton = new ButtonClass();
	LoadTGA(&OKbutton->button[0],"Textures/ok.tga");
	LoadTGA(&OKbutton->button[1],"Textures/ok.tga");
	OKbutton->Set(240,580,400,460);
	ListofButtons.push_back(OKbutton);

	//Day progress
	day = 1;
	Dtimer = 0;

	spritectime = 0, spriteptime = 0, tctime = 0, tptime = 0, timer = 300;

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
		GameObject* catcher2 = (GameObject*)catcher;
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
	//cout << "minigame status: " << minigameobjects->minigame << endl;

	if (sizechanged)
		{
			OKbutton->Set(240,580,400,460);
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
			Dtimer++;
			
			if (Dtimer >= 300)
			{
				day +=1;
				REvent.IsDisplay = true;
				REvent.Random();
				REvent.CreateEventz(REvent.type);
				cout <<REvent.type<<endl;
				theCamera->canPan = false;
				Dtimer = 0;
			}
		}

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
				}
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
			}
		}
		
		//START FOR ALL OF MINI GAME==================================================
		//for mini game animation
	static int frame = 0;
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	++frame;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float dt = (time - lastTime) / 1000.f;

	lastTime = time;

	minigameobjects->spawntime -= dt*0.001;

	tctime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval2 = tctime - tptime;

	if(minigameobjects->minigame)
	{
		if(timeInterval2 > 1000)
		{
			tptime = tctime;
			timer--;
			if(timer <= 0)
			{
				timer = 0;
			}
		}
	}

	spritectime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = spritectime - spriteptime;
	if(timeInterval > 150)
	{
		spriteptime = spritectime;
		minigameobjects->mgctr++;
	}

	if (minigameobjects->mgctr == 7)
	{
		minigameobjects->mgctr = 0;
	}


	if(minigameobjects->minigame)
	{
		for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *mg = (GameObject *)*it;
			if(mg->active)
			{
				if(mg->type == GameObject::GO_COIN)
				{//coin falling update
					/*mg->vel +=  minigameobjects->gravity * dt;*/
					mg->vel.y = -200;
					if(mg->vel.y <= -200)
					{mg->vel.y = -200;}
					mg->pos += minigameobjects->fallspeed * (mg->vel + (mg->vel + minigameobjects->gravity * dt)) * 0.5 * dt;

					/*if(mg->pos.y <= (600 - 200 + theCamera->GetPosition().y - 350))*/
					if(mg->pos.y <= catcher->pos.y)
					{
						mg->vel.y = -200;
						mg->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
						mg->pos.y = 600 - Math::RandIntMinMax(110, 310) + theCamera->GetPosition().y - 300;
					}

					if(catcher->active)
					{
						if(catcher->type == GameObject::GO_CATCHER)
						{
							if((catcher->pos-mg->pos).Length()<=60)
							{
								mg->counter--;
								it = m_goList.erase(it);
								resource.SetMoney(resource.GetMoney()+100);

								if(mgsfx == NULL)
								{
									mgsfx = theSoundEngine->play2D ("SFX/coin.wav", false, true);
								}else
								{
									mgsfx == NULL;
									mgsfx = theSoundEngine->play2D ("SFX/coin.wav", false, true);
								}
								if(mgsfx->getIsPaused() == true)
								{
									mgsfx->setIsPaused(false);
								}
								else if(mgsfx->isFinished() == true)
								{
									mgsfx = NULL;
								}
								break;
							}
							if(catcher->pos.x <= 150){catcher->pos.x = 150;}
							if(catcher->pos.x >= 590){catcher->pos.x = 590;}
						}

					}
				}
			}
			else if((minigameobjects->spawntime <= 0) && (mg->counter < MAX_COIN) && timer > 0)
			{
				minigameobjects->spawntime = SPAWN_TIME;
				GameObject *mg2 = new GameObject(GameObject::GO_COIN);
				mg2->vel.y = -200;
				if(mg2->vel.y <= -200)
				{mg2->vel.y = -200;}
				mg2->active = true;
				mg2->counter++;
				mg2->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
				mg2->pos.y = 600 - Math::RandIntMinMax(110, 150) + theCamera->GetPosition().y - 300;
				m_goList.push_back(mg2);
				break;
			}
		}
	}
		//END FOR ALL OF MINI GAME==================================================

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
				myTile[y][x].SetType(3);
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
	glDisable(GL_TEXTURE_2D);


	//for mini game
	if(minigameobjects->minigame)
	{
		//DRAW THIS STUFF IN THE MINIGAME CLASS PLEASE
		glPushMatrix();
		glTranslatef(150,50,-1);
		glBindTexture (GL_TEXTURE_2D, MGBackgroundTexture.id);
		minigameobjects->DrawMGBG();

		//rendering of coins
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *mg = (GameObject *)*it;
			if (mg->active)
			{
				glPushMatrix();
				glTranslatef(0,0,-5);
				minigameobjects->DrawObject(mg, CoinTexture.id);
				glPopMatrix();
			}
		}
		//rendering of catcher
		GameObject *catcher2 = (GameObject *)catcher;
			if (catcher2->active)
			{
				glPushMatrix();
				glTranslatef(0,0,-5);
				minigameobjects->DrawObject(catcher2, CatcherTexture.id);
				glPopMatrix();
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
	//Enable 2D text display and HUD
	theCamera->SetHUD( true);
	//print(our_font,0,550,"Cam posX :%f\nCam posY :%f\nCam PosZ:%f",theCamera->GetPosition().x ,theCamera->GetPosition().y,theCamera->GetPosition().z);
	/*print(our_font,0,height-100,"type: %d",myTile[SelectorY][SelectorX].GetBtype());
	print(our_font,0,height-600,"OwnerName: %s",myTile[SelectorY][SelectorX].myHouse.GetOwner().c_str());
	print(our_font,0,height-200,"screenW: %f\nscreenH: %f",width,height);
	print(our_font,0,height-350,"pickX: %d\npickY: %d",SelectorX,SelectorY);
	print(our_font,0,height-500,"MouseX: %d\nMouseY: %d",mouseInfo.lastX,mouseInfo.lastY);*/
	print(our_font,0,height-300,"Day: %d\n", day);
	print(our_font,0,height-400,"Timer: %d\n", Dtimer);

	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{	
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			//Citizens->MoodUpdate(Citizen::EATINGPLACE, Citizen::FOOD);
			//print(our_font,0,height-500,"MouseX: %s",Citizens->GetName().c_str());
		}
	}
	RenderUI();
	TheChoice->Draw();
	if (REvent.IsDisplay == true)
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
		}
	}
}