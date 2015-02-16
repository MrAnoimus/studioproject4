#include "GameStateManager.h"
#include "IntroState.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

CGameStateManager theGSM;

void changeSize(int w, int h)
{
	CGameState* state = theGSM.getActiveState();
	state->changeSize(w,h);
}

void renderScene(void)
{
	theGSM.Draw();
	//myApplication::getInstance()->renderScene();
}
void updateScene(void)
{
	theGSM.Update();
	theGSM.HandleEvents();
}
void inputKey(int key, int x, int y)
{
	//myApplication::getInstance()->inputKey(key,x,y);
}

void KeyboardDown(unsigned char key, int x, int y)
{
	//theGSM.KeyboardDown(key,x,y);
	CGameState* state = theGSM.getActiveState();
	state->KeyboardDown(key,x,y);
	//myApplication::getInstance()->KeyboardDown(key,x,y);
}

void KeyboardUp(unsigned char key, int x, int y)
{
	//theGSM.KeyboardUp(key,x,y);
	CGameState* state = theGSM.getActiveState();
	state->KeyboardUp(key,x,y);
}

void MouseMove(int x, int y)
{
	CGameState* state = theGSM.getActiveState();
	state->MouseMove(x,y);
}

void MouseClick(int button, int states, int x, int y)
{
	CGameState* state = theGSM.getActiveState();
	state->MouseClick(button,states,x,y);
}

void CleanUpUponExit(void)
{

}

int main(int argc, char **argv )
{
	//Read a value from the lua text file
	lua_State *L2 = lua_open();
	luaL_openlibs(L2);
	if (luaL_loadfile(L2, "LuaScript/config.lua") || lua_pcall(L2, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L2, -1));
		return -1;
	}

	lua_getglobal(L2,"PROGRAM_NAME");
	lua_getglobal(L2,"PROGRAM_VERSION");
	lua_getglobal(L2, "SCREENWIDTH");
	lua_getglobal(L2, "SCREENHEIGHT");
	lua_getglobal(L2, "COLORDEPTH");
	lua_getglobal(L2, "WPOS_X");
	lua_getglobal(L2, "WPOS_Y");
	lua_getglobal(L2, "FULLSCREEN");
	
	std::string PROGRAM_NAME = lua_tostring(L2, 1);
	std::string PROGRAM_VERSION  = lua_tostring(L2,2);
	int SCREENWIDTH = (int)lua_tonumber(L2, 3);
	int SCREENHEIGHT = (int)lua_tonumber(L2, 4);
	int COLORDEPTH = (int)lua_tonumber(L2, 5);
	int WPOS_X = (int)lua_tonumber(L2, 6);
	int WPOS_Y = (int)lua_tonumber(L2, 7);
	bool FULLSCREEN = (bool)lua_toboolean(L2,8);
	printf("PROGRAM_NAME: %s \nPROGRAM_VERSION: %s \nSCREENWIDTH: %d\nSCREENHEIGHT: %d\nCOLORDEPTH: %d\nWPOS_X: %d\nWPOS_Y: %d\nFULLSCREEN: %s\n", PROGRAM_NAME.c_str (),PROGRAM_VERSION.c_str(), SCREENWIDTH, SCREENHEIGHT,COLORDEPTH,WPOS_X,WPOS_Y,FULLSCREEN? "true" : "false");	

	lua_close(L2);
	// initialize the engine
	theGSM.Init( "Game State Test" );
	//glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WPOS_X,WPOS_Y);
	glutInitWindowSize(SCREENWIDTH,SCREENHEIGHT);
	glutCreateWindow(PROGRAM_NAME.c_str());

	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);
	glutIdleFunc(updateScene);
	if(FULLSCREEN == true)
	{
		glutFullScreen();
	}
	
//	glutSpecialFunc(inputKey);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutPassiveMotionFunc(MouseMove);
	glutMouseFunc(MouseClick);// for mouse click
	atexit(CleanUpUponExit);

	// load the intro
	theGSM.ChangeState( CIntroState::Instance() );

	// main loop
	while(theGSM.Running())
	{
		theGSM.HandleEvents();
		theGSM.Update();
		theGSM.Draw();
		glutMainLoop();
	}

	// cleanup the Game State Manager
	theGSM.Cleanup();
	return 0;
}