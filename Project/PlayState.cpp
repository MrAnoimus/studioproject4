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
											homeless--;
											break;
										}
										if(i>=1)
										{				
											Citizens->CitizenDestination->DestinationList.push_back(TheNode);
											break;
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
							if(myTile[SelectorY][SelectorX].GetBtype() == 1 )
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								Map[SelectorY][SelectorX] = 1;
								myTile[SelectorY][SelectorX].Tag ="house";
								if(myTile[SelectorY][SelectorX].GetFull() == false)
								{
									resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myHouse.GetCost());
									housecount+=1;
									resource.SetManpower(resource.GetManPower() -1);
								}
								
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 2)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								
								Map[SelectorY][SelectorX]=2;
								myTile[SelectorY][SelectorX].Tag ="eatingplace";
								if(myTile[SelectorY][SelectorX].GetFull() == false)
								{
									resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myFCourt.GetCost());
									FcourtCount+=1;
								}
								
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 3)
							{
								//once selected and click on set tile to not empty
								myTile[SelectorY][SelectorX].SetEmpty(false);
								Map[SelectorY][SelectorX]=3;
								myTile[SelectorY][SelectorX].Tag ="workplace";
								if(myTile[SelectorY][SelectorX].GetFull() == false)
								{
									resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myGstore.GetCost());
									GstoreCount +=1;
								}
								
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 5)
							{
								if(myTile[SelectorY][SelectorX].GetEmpty())
								{
									resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myObstacle.GetCost());
								}
							}
							else if(myTile[SelectorY][SelectorX].GetBtype() == 6)
							{
								if(myTile[SelectorY][SelectorX].GetEmpty())
								{
									resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myDebris.GetCost());
								}
							}
							for(int y = 0; y < ROWS; y += 1)
							{
								for(int x = 0; x < COLS; x += 1)
								{
									if(myTile[SelectorY][SelectorX].GetBtype() == 5)
									{
										//once selected and click on set tile to not empty
										myTile[y][x].SetEmpty(false);
										Map[SelectorY][SelectorX]=10;
										//myTile[y][x].Tag = "nothing";
									}
									if(myTile[SelectorY][SelectorX].GetBtype() == 6)
									{
										//once selected and click on set tile to not empty
										myTile[y][x].SetEmpty(false);
										//resource.SetMoney(resource.GetMoney()-myTile[SelectorY][SelectorX].myDebris.GetCost());
										Map[SelectorY][SelectorX]=10;

										//myTile[y][x].Tag = "nothing";
									}
								}
							}

							if(myTile[SelectorY][SelectorX].GetBtype()==1||myTile[SelectorY][SelectorX].GetBtype()==2||myTile[SelectorY][SelectorX].GetBtype()==3)
							{
								//update the previous house owners and update the place around their house to update their happiness level.
								for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
								{
									Citizen *Citizens = *it;
									if(myTile[SelectorY-1][SelectorX].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,3);
									}
									else if(myTile[SelectorY+1][SelectorX].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,2);
									}
									else if(myTile[SelectorY][SelectorX-1].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,1);
									}
									else if(myTile[SelectorY][SelectorX+1].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,0);
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
				//for existing citizens when game already start
				//for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
				//	{
				//		
				//		Citizen *Citizens = *it;
				//		Astar as(px,py,1,1);
				//		//
				//		bool result = as.Search(Map);

				//		CNode* Node = new CNode;
				//		Node->x = 1;
				//		Node->y = 1;
				//		//
				//		as.AddCloseList(Node);
				//		if(result)
				//		{
				//			moving = true;
				//			for(int i=0;i<(int)as.closeList.size();i++)
				//			{
				//				//Citizen stuff
				//				CNode* TheNode = new CNode();
				//				TheNode->x = as.closeList[i]->x*100;
				//				TheNode->y = as.closeList[i]->y*100;
				//				cout <<"Size: " <<(int)as.closeList.size() <<std::endl;
				//				for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
				//				{
				//					int j= (int)as.closeList.size();
				//					Citizen *Citizens = *it;
				//					if (Citizens->active == true&&Citizens->Movedout==true)
				//					{
				//						
				//						if(i+1>=j)
				//						{
				//							Citizens->CitizenDestination->DestinationList.push_back(TheNode);
				//							
				//							Citizens->owner = Citizens->GetName();
				//							Citizens->SetPlace(myTile[SelectorY][SelectorX-1].Tag, 0);
				//							Citizens->SetPlace(myTile[SelectorY][SelectorX+1].Tag, 1);
				//							Citizens->SetPlace(myTile[SelectorY-1][SelectorX].Tag, 2);
				//							Citizens->SetPlace(myTile[SelectorY+1][SelectorX].Tag, 3);
				//							Citizens->Movedout=false;
				//							break;
				//						}
				//						if(i>=1)
				//						{				
				//							Citizens->CitizenDestination->DestinationList.push_back(TheNode);
				//							break;
				//						}
				//					}
				//				}
				//			}
				//		}
				//	}
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
							myTile[SelectorY][SelectorX].SetEmpty(true);
							
							Map[SelectorY][SelectorX]=220;
							myTile[SelectorY][SelectorX].SetBtype(6);
							//minus one house
							housecount-=1;
							resource.SetManpower(resource.GetManPower() +1);
						}
						if(myTile[SelectorY][SelectorX].GetBtype() == 2)
						{
							myTile[SelectorY][SelectorX].SetEmpty(true);
							myTile[SelectorY][SelectorX].SetBtype(6);
							Map[SelectorY][SelectorX]=220;
							FcourtCount -=1;
						}
						if(myTile[SelectorY][SelectorX].GetBtype() == 3)
						{
							myTile[SelectorY][SelectorX].SetEmpty(true);
							myTile[SelectorY][SelectorX].SetBtype(6);
							Map[SelectorY][SelectorX]=220;
							GstoreCount -= 1;
						}
						if(myTile[SelectorY][SelectorX].GetBtype()==1||myTile[SelectorY][SelectorX].GetBtype()==2||myTile[SelectorY][SelectorX].GetBtype()==3)
							{
								//update the previous house owners and update the place around their house to update their happiness level.
								for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
								{
									Citizen *Citizens = *it;
									if(myTile[SelectorY-1][SelectorX].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,3);
									}
									else if(myTile[SelectorY+1][SelectorX].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,2);
									}
									else if(myTile[SelectorY][SelectorX-1].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,1);
									}
									else if(myTile[SelectorY][SelectorX+1].myHouse.GetOwner()==Citizens->GetName())
									{
										Citizens->SetPlace(myTile[SelectorY][SelectorX].Tag,0);
									}
								}
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
				if(Citizens->active==true)
				{
					Citizens->RenderMood!= Citizens->RenderMood;
				}
			}
		}

	
		if(myKeys['k'] == true)
		{
			ofstream fout("LuaScript/Save/save2.txt");
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

			ofstream fout2("LuaScript/Save/resource.lua");
			if(fout2.is_open())
			{
				fout2<<"FOOD = "<<resource.GetFood()<<endl;
				fout2<<"MONEY = "<<resource.GetMoney()<<endl;
				fout2<<"MANPOWER = "<<resource.GetManPower()<<endl;
				fout2<<"CITIZEN = "<<resource.GetCitizen()<<endl;
			}
			fout2.close();

			ofstream fout3("LuaScript/Save/save3.txt");
			if(fout3.is_open())
			{
				for(int y = 0; y < ROWS; y ++ )
				{
					for(int x = 0; x < COLS; x ++ )
					{
						if(myTile[y][x].GetBtype() == 1)
						{
							fout3<<myTile[y][x].myHouse.GetOwner()<<" ";
						}
					}
				}
			}
			fout3.close();
		}

		if(myKeys['l'] == true)
		{
			cout <<endl;		
		}
		}
}
void CPlayState::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
}
bool CPlayState::Init()
{
	
	if (resource.GetLoad() == 1)
	{
		ifstream ifile("LuaScript/Save/save2.txt");
		for (int y = 0; y < ROWS; y ++ )
		{
			for(int x = 0; x < COLS; x ++ )
			{
				ifile>> Map[y][x];
				cout << Map[y][x] <<",";
			}
		}
	}

	else if (resource.GetLoad()==0)
	{
		ifstream ifile("LuaScript/Save/DefaultM.txt");
		for (int y = 0; y < ROWS; y ++ )
		{
			for(int x = 0; x < COLS; x ++ )
			{
				ifile>> Map[y][x];
				cout << Map[y][x] <<",";
			}
		}
	}
	cout <<endl;
	for(int y = 0; y < ROWS; y ++ )
	{
		for(int x = 0; x < COLS; x ++ )
		{
			//if(myTile[y][x].GetBtype() == 1)
			//{
			cout<<myTile[y][x].GetBtype()<<",";
			//}
		}
	}


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

	lua_close(L2);

	checker =0;
	//load
	if (resource.GetLoad() ==1)
	{
		lua_State *L3 = lua_open();
		luaL_openlibs(L3);
		if (luaL_loadfile(L3, "LuaScript/Save/resource.lua") || lua_pcall(L3, 0, 0, 0))
		{
			printf("error: %s", lua_tostring(L3, -1));
			return -1;
		}
		//sets the player resources;
		lua_getglobal(L3,"FOOD");
		int food = lua_tointeger(L3,1);
		resource.SetFood(food);

		lua_getglobal(L3,"MONEY");
		int money= lua_tointeger(L3,2);
		cout <<money;
		resource.SetMoney(money);

		lua_getglobal(L3, "MANPOWER");
		int manpower = lua_tointeger(L3,3);
		cout <<manpower;
		resource.SetManpower(manpower);

		lua_getglobal(L3,"CITIZEN");
		int numOfCitizen= lua_tointeger(L3,4);
		cout <<numOfCitizen;
		resource.SetCitizen(numOfCitizen);
		lua_close(L3);
	}
	//dont load
	if (resource.GetLoad() ==0)
	{
		lua_State *L3 = lua_open();
		luaL_openlibs(L3);
		if (luaL_loadfile(L3, "LuaScript/Save/defaultR.lua") || lua_pcall(L3, 0, 0, 0))
		{
			printf("error: %s", lua_tostring(L3, -1));
			return -1;
		}
		//sets the player resources;
		lua_getglobal(L3,"FOOD");
		int food = lua_tointeger(L3,1);
		resource.SetFood(food);

		lua_getglobal(L3,"MONEY");
		int money= lua_tointeger(L3,2);
		cout <<money;
		resource.SetMoney(money);

		lua_getglobal(L3, "MANPOWER");
		int manpower = lua_tointeger(L3,3);
		cout <<manpower;
		resource.SetManpower(manpower);

		lua_getglobal(L3,"CITIZEN");
		int numOfCitizen= lua_tointeger(L3,4);
		cout <<numOfCitizen;
		resource.SetCitizen(numOfCitizen);
		lua_close(L3);
	}

	//camera data and init
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 400, 300, -500.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );
	angle = 0.0f;
	frequency = 30.0f;
	//data used for testing 
	//
	//load texture here
	LoadTGA(&BGTEST,"Textures/bg2.tga");
	LoadTGA(&BackgroundTexture,"Textures/Farmbg.tga");
	LoadTGA(&MenuTexture[0],"Textures/redbg.tga");
	LoadTGA(&MenuTexture[1],"Textures/greenbg.tga");
	LoadTGA(&ResultTexture[0],"Textures/WinScreen.tga");
	LoadTGA(&ResultTexture[1],"Textures/LosingScreen.tga");


	//load ttf fonts
	our_font.init("Fonts/FFF_Tusj.TTF", 42);
	//init keyboard values
	housecount =0;
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
		/*cout <<"Random "<<Random<<endl;
		cout <<"Random2 "<<Random2<<endl;*/
		if(Random == Random2)
		{
			srand((unsigned int)i*i);
			Random = rand()%3+1;
		}
		
		/*cout <<"After Random "<<Random<<endl;
		cout <<"After Random2 "<<Random2<<endl;*/
		
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
		homeless++;

		ifstream myFile;
		myFile.open("Names/namesM.txt");
		string rnames[50]; // holds the 50 names in the file.

		int x = 0;
		int randNum;
		while (myFile.good())
		{
			getline(myFile, rnames[x]);
			x++;
		}
		srand((unsigned int) i);
		
		/*randNum = Math::RandIntMinMax(0, 49);*/
		randNum = rand() % 50 + 1;
		rNAME = rnames[randNum];
	
		myFile.close();

		//go->SetName(rNAME);
	}

		//herez
	for (int y = 0; y < ROWS; y ++ )
	{
		for(int x = 0; x < COLS; x ++ )
		{
			if (Map[y][x] == 1)
			{
				for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
				{
					
					Citizen *Citizens = *it;
					if(Citizens->active==true&&Citizens->Movedout==false)
					{
					myTile[y][x].myHouse.SetOwner(Citizens->GetName());
					Citizens->owner = Citizens->GetName();
					Citizens->SetPosition(Vector3D (10 + x*100,y*100,-1) );	
					Citizens->Movedout=true;
					homeless--;
					break;
					}
					
				}
			}
		}
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
	returnbutton->Set(340,480,330,370);
	ListofButtons.push_back(returnbutton);

	daypassed = 1;

	//load ttf fonts
	minigameobjects->mgfont.init("Fonts/GretoonHighlight.TTF", 72);

	OKbutton = new ButtonClass();
	LoadTGA(&OKbutton->button[0],"Textures/okup.tga");
	LoadTGA(&OKbutton->button[1],"Textures/okdown.tga");
	OKbutton->Set(350,450,400,460);
	ListofButtons.push_back(OKbutton);

	//game ui buttons
	NormSpeed = new ButtonClass();
	LoadTGA(&NormSpeed->button[0],"Textures/normalspeedup.tga");
	LoadTGA(&NormSpeed->button[1],"Textures/normalspeeddown.tga");
	NormSpeed->Set(680,695,150,165);
	ListofButtons.push_back(NormSpeed);

	MinSpeed = new ButtonClass();
	LoadTGA(&MinSpeed->button[0],"Textures/minutespeedup.tga");
	LoadTGA(&MinSpeed->button[1],"Textures/minutespeeddown.tga");
	MinSpeed->Set(705,735,150,165);
	ListofButtons.push_back(MinSpeed);

	HrSpeed = new ButtonClass();
	LoadTGA(&HrSpeed->button[0],"Textures/hourspeedup.tga");
	LoadTGA(&HrSpeed->button[1],"Textures/hourspeeddown.tga");
	HrSpeed->Set(745,790,150,165);
	ListofButtons.push_back(HrSpeed);

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

	Savebutton = new ButtonClass();
	LoadTGA(&Savebutton->button[0],"Textures/save.tga");
	LoadTGA(&Savebutton->button[1],"Textures/save.tga");
	Savebutton->Set(600,650,0,50);
	ListofButtons.push_back(Savebutton);
	//get amount of building etc
	for(int y = 0; y < ROWS; y += 1)
	{
		for(int x = 0; x < COLS; x += 1)
		{
			if(Map[y][x] == 1)
			{
				housecount+=1;
			}
			if(Map[y][x] == 2)
			{
				FcourtCount+=1;
			}
			if(Map[y][x] == 3)
			{
				GstoreCount+=1;
			}
		}
	}


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

	if(myKeys['h'] == true)
	{
		resource.SetWin(0);
		theGSM->ChangeState( CResultState::Instance() );

	}

		if(myKeys['j'] == true)
	{
		resource.SetWin(1);
		theGSM->ChangeState( CResultState::Instance() );

	}

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
	cout << homeless << endl;
	if(myGameUI.myGameTime.GetDay()==1&&myGameUI.myGameTime.GetHour()==12&&myGameUI.myGameTime.GetMinute()==0&&myGameUI.myGameTime.GetSecond()==0)
	{
		TheChoice->SetPopup(true);
	}
	if(DestoryedChance>0)
	{
		float Destroyed=0;
		srand(time(NULL));
		Destroyed = rand()%100;
		srand(time(NULL));
		cout << "Chance" << Destroyed << endl;
		if(Destroyed <= DestoryedChance)
		{
			for(int y = 0; y < ROWS; y += 1)
			{
				for(int x = 0; x < COLS; x += 1)
				{
					if(Map[y][x] == 1)
					{
						Map[y][x] = 220;
					}
				}
			}
		}
		
	}
	
	checker = 0;

	if(NormSpeed->buttonclicked)
	{
		myGameUI.myGameTime.Fincrement = 10;
		myGameUI.myGameTime.HrIncrement = 1;
		mouseInfo.mLButtonUp = false;
		NormSpeed->buttonclicked = false;
	}

	if(MinSpeed->buttonclicked)
	{
		myGameUI.myGameTime.Fincrement = 100;
		mouseInfo.mLButtonUp = false;
		MinSpeed->buttonclicked = false;
	}

	if(HrSpeed->buttonclicked)
	{
		myGameUI.myGameTime.Fincrement = 100;
		myGameUI.myGameTime.HrIncrement = 3;
		mouseInfo.mLButtonUp = false;
		HrSpeed->buttonclicked = false;
	}

	if(myKeys['r'] == true)
	{
		resource.SetWin(0);
		theGSM->ChangeState( CResultState::Instance() );
	}
	if(myKeys['t'] == true)
	{
		resource.SetWin(1);
		theGSM->ChangeState( CResultState::Instance() );
	}
	static int lastTime = GetTickCount();
	++frameCount;
	int time = GetTickCount();
	deltaTime = (time - lastTime) / 1000.f;
	
	if (myGameUI.myGameTime.daycheck == true)
	{
		REvent.IsDisplay = true;
		REvent.Random();
		REvent.CreateEventz(REvent.type);
		calculateEarning();
		theCamera->canPan = false;
		myGameUI.myGameTime.daycheck = false;
		daypassed++;
	}

	if(daypassed %2 == 0 && resource.GetMoney() <= 800)
	{
		myGameUI.myGameTime.Fincrement = 10;
		myGameUI.myGameTime.HrIncrement = 1;
		minigameobjects->minigame = true;
		minigameobjects->playing = true;
		daypassed = 1;
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
		returnbutton->buttonclicked = false;
	}

	if (sizechanged)
	{
		OKbutton->Set(240,580,400,460);
		returnbutton->Set(340,480,330,370);
		Choice1->Set(300,520,460,520);
		Choice2->Set(350,450,520,580);
		Savebutton->Set(600,650,0,50);
		NormSpeed->Set(680,695,150,165);
		MinSpeed->Set(705,735,150,165);
		HrSpeed->Set(745,790,150,165);
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
		DestoryedChance=20;
	}
	if(Choice2->buttonclicked)
	{
		TheChoice->popup = false;
		mouseInfo.mLButtonUp = false;
		Choice2->buttonclicked = false;
	}

	if(Savebutton->buttonclicked)
	{
		ofstream fout("LuaScript/Save/save2.txt");
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

		ofstream fout2("LuaScript/Save/resource.lua");
		if(fout2.is_open())
		{
			fout2<<"FOOD = "<<resource.GetFood()<<endl;
			fout2<<"MONEY = "<<resource.GetMoney()<<endl;
			fout2<<"MANPOWER = "<<resource.GetManPower()<<endl;
			fout2<<"CITIZEN = "<<resource.GetCitizen()<<endl;
		}
		fout2.close();

		ofstream fout3("LuaScript/Save/save3.txt");
		if(fout3.is_open())
		{
			for(int y = 0; y < ROWS; y ++ )
			{
				for(int x = 0; x < COLS; x ++ )
				{
					if(myTile[y][x].GetBtype() == 1)
					{
						fout3<<myTile[y][x].myHouse.GetOwner()<<" ";
					}
				}
			}
		}
		fout3.close();
		Savebutton->buttonclicked = false;
	}
	
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{
		Citizen *Citizens = *it;

		if (Citizens->GetMood() == "ENRAGED")
		{
			checker ++;
			cout <<"checker" <<checker<<endl;
			if (checker >=5)
			{
				resource.SetWin(1);
				theGSM->ChangeState( CResultState::Instance() );
			}
		}
	}
	
	
	//conditions
	//if (resource.GetMoney() <= 0)
	//{
	//	resource.SetWin(1);
	//	theGSM->ChangeState( CResultState::Instance() );
	//}

	if (myGameUI.myGameTime.GetDay() == 4)
	{
		resource.SetWin(0);
		theGSM->ChangeState( CResultState::Instance() );
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
							if(Citizens->MovedBack==false)
							{
								if ((position -Citizens->GetPosition()).LengthSquared() > (0))
								{
									Vector3D direction(position - Citizens->GetPosition());
									Citizens->Position.x += direction.Normalized().x;
									Citizens->Position.y += direction.Normalized().y;
									Citizens->AnimationInvert=false;
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
									Citizens->AnimationInvert=true;
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
										Citizens->sheltered=false;
										homeless++;
										while(Citizens->index<Citizens->CitizenDestination->DestinationList.size()-1)
										{
											Citizens->index++;
											Citizens->CitizenDestination->DestinationList[Citizens->index]->x=100;
											Citizens->CitizenDestination->DestinationList[Citizens->index]->y=100;
										}
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
						if(myTile[y][x].GetModeOn()==false)
						{
							Citizens->RenderMood=false;
						}
						if(myTile[y][x].GetPosition().x+50>=Citizens->GetPosition().x
							&&myTile[y][x].GetPosition().x-50<=Citizens->GetPosition().x
							&&myTile[y][x].GetPosition().y+50>=Citizens->GetPosition().y
							&&myTile[y][x].GetPosition().y-50<=Citizens->GetPosition().y)
							{
								if(myTile[y][x].GetFull()==false)
								{
									if(myTile[y][x].myHouse.GetOwner()==Citizens->GetName())
									{
										myTile[y][x].myHouse.SetOwner(" ");
										Citizens->MovedBack=true;
									}
								}
								else if(myTile[y][x].GetEmpty()==true)
								{
									if(myTile[y][x].myHouse.GetOwner()==Citizens->GetName())
									{
										myTile[y][x].myHouse.SetOwner(" ");
										Citizens->MovedBack=true;
									}
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
				for(int y = 0; y < ROWS; y += 1)
				{
					for(int x = 0; x < COLS; x += 1)
					{
						if(myTile[y][x].GetModeOn()==false)
						{
							Citizens->RenderMood=false;
						}
					}
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
			if(Map[y][x] == 220)
			{
				myTile[y][x].SetType(4);
				myTile[y][x].SetBtype(6);
			}
			if(Map[y][x] == 1)
			{//
				myTile[y][x].SetFull(true);
				myTile[y][x].SetBtype(1);
				myTile[y][x].Tag = "house";
			}
			if(Map[y][x] == 2)
			{
				myTile[y][x].SetBtype(2);
				myTile[y][x].Tag = "eatingplace";
			}
			if(Map[y][x] == 3)
			{
				myTile[y][x].SetBtype(3);
				myTile[y][x].Tag = "workplace";
			}
			if(Map[y][x] == 4)
			{
				myTile[y][x].SetBtype(4);
			}
			if(Map[y][x] == 10)
			{
				myTile[y][x].SetFull(false);
				myTile[y][x].SetType(0);//tile color code
			}
			Vector3D temp(50 + x*100,50 +y*100,-1);
			myTile[y][x].SetPosition(temp);
			myTile[y][x].Draw();
		}
	}

			
}
void CPlayState::checkUIName()
{
	if(myTile[SelectorY][SelectorX].GetBtype() == 1)
	{
		Bnames = "House";
		cost = myTile[SelectorY][SelectorX].myHouse.GetCost();
	}
	if(myTile[SelectorY][SelectorX].GetBtype() == 2)
	{
		Bnames = "Foodstore";
		cost = myTile[SelectorY][SelectorX].myFCourt.GetCost();
	}
	if(myTile[SelectorY][SelectorX].GetBtype() == 3)
	{
		Bnames = "General store";
		cost = myTile[SelectorY][SelectorX].myGstore.GetCost();
	}
	if(myTile[SelectorY][SelectorX].GetBtype() == 4)
	{
		Bnames = "Shelter";
		cost = myTile[SelectorY][SelectorX].myShelter.GetCost();
	}
	if(myTile[SelectorY][SelectorX].GetBtype() == 5)
	{
		Bnames = "Tree";
		cost = myTile[SelectorY][SelectorX].myObstacle.GetCost();
	}
	if(myTile[SelectorY][SelectorX].GetBtype() == 6)
	{
		Bnames = "Debris";
		cost = myTile[SelectorY][SelectorX].myDebris.GetCost();
	}
}
void CPlayState::Draw(CGameStateManager* theGSM) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	theCamera->Update();

	minigameobjects->theCamera = theCamera;
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture (GL_TEXTURE_2D, BackgroundTexture.id);
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
	
	glPushMatrix();
		//glColor3f(1,1,1);
		glBindTexture (GL_TEXTURE_2D, BGTEST.id);
		glTranslatef(0,200,0);
		glPushMatrix();
			glBegin(GL_QUADS);
			glTexCoord2f(1,1);
			glVertex2f(-width,height);
			glTexCoord2f(0,1);
			glVertex2f(width,height);
			glTexCoord2f(0,0);
			glVertex2f(width,-height);
			glTexCoord2f(1,0);
			glVertex2f(-width,-height);				
		glEnd();
		glPopMatrix();
	glPopMatrix();


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);


	//
	if(minigameobjects->minigame)
	{
		glTranslatef(0,0,-10);
		minigameobjects->Draw();
	}
	glPushMatrix();
	DrawTileContent();
	glPopMatrix();
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glPushMatrix();
	for (std::vector<Citizen *>::iterator it = CitizenList.begin(); it != CitizenList.end(); ++it)
	{	
		
		//here
		Citizen *Citizens = *it;
		if (Citizens->active == true)
		{
			Citizens->Draw(SelectorX*100,SelectorY*100);
		}
	}
	glPopMatrix();
	
	
	//Enable 2D text display and HUD
	theCamera->SetHUD( true);
	
	checkUIName();
	myGameUI.Draw(width-200,height - 50,Bnames.c_str(),cost,myTile[SelectorY][SelectorX].GetModeOn());
	myGameUI.DrawSelect(750,200,myTile[SelectorY][SelectorX].GetModeOn(),myTile[SelectorY][SelectorX].GetBtype());
	//money manpower citizen
	myGameUI.DrawResource(myGameUI.GetIconSize(),myGameUI.GetIconSize());
	myGameUI.DrawResourceData(myGameUI.GetSize()*2,height-myGameUI.GetSize()*2,resource.GetMoney(),resource.GetCitizen(),resource.GetManPower(),resource.GetMaxManPower());
	//print(our_font,0,250,"PickX :%d PickY:%d",SelectorX,SelectorY);
	//print(our_font,0,250,"house number : %d",housecount);
	print(our_font,0,250,"empty? : %d",myTile[SelectorY][SelectorX].GetFull());

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
	Savebutton->Render();
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
void CPlayState::RenderUI(void)
{
	
	NormSpeed->Render();
	MinSpeed->Render();
	HrSpeed->Render();

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
void CPlayState::calculateEarning()
{
	float H_Fee = housecount * myTile[SelectorY][SelectorX].myHouse.GetMaintenanceFee();
	float FC_Fee = FcourtCount * myTile[SelectorY][SelectorX].myFCourt.GetMaintenanceFee();
	float GS_Fee = GstoreCount * myTile[SelectorY][SelectorX].myGstore.GetMaintenanceFee();
	float TotalFee = H_Fee + FC_Fee + GS_Fee;
	
	float FC_Earning = FcourtCount * myTile[SelectorY][SelectorX].myFCourt.GetEarnings();
	float GS_Earning = GstoreCount * myTile[SelectorY][SelectorX].myGstore.GetEarnings();
	float ShelterFund;
	if(myGameUI.myGameTime.GetDay() %  3 == 0 )
	{
		ShelterFund = myTile[SelectorY][SelectorX].myShelter.GetEarnings();
	}else
	{
		ShelterFund = 0;
	}
	float myEarning = FC_Earning + GS_Earning + ShelterFund;
	resource.SetMoney(resource.GetMoney() + myEarning -TotalFee );
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
	//std::string str = go->GetName() + ss.str();

	go->SetName(rNAME + ss.str());
	//go->SetName(str);

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