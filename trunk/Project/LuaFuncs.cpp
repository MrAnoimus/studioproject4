#include "LuaFuncs.h"

LuaFuncs *LuaFuncs::instance = NULL;

LuaFuncs::LuaFuncs(): L(lua_open())
{
}

LuaFuncs *LuaFuncs::getInstance()
{
	if (instance == NULL)
		instance = new LuaFuncs();
	return instance;
}

//LuaFuncs::~LuaFuncs(void)
//{
//}

void LuaFuncs::SetLUA(bool mode)
{
	//Open
	if (mode)
	{
		L = lua_open();
		luaL_openlibs(L);

		luaL_loadfile(L, "LuaScript/config.lua");
		lua_pcall(L, 0, 0, 0);
	}

	//Close
	else lua_close(L);
}

//True = Width, False = Height
int LuaFuncs::GetScreen(bool mode)
{
	SetLUA(true);

	lua_getglobal(L, "SCREENWIDTH");
	lua_getglobal(L, "SCREENHEIGHT");

	if (mode)
		return (int)lua_tonumber(L, 1);
	else
		return (int)lua_tonumber(L, 2);

	SetLUA(false);
}

//True = Program Name, False = Version
string LuaFuncs::GetName(bool mode)
{
	SetLUA(true);

	lua_getglobal(L, "PROGRAM_NAME");
    lua_getglobal(L, "PROGRAM_VERSION"); 

	if (mode)
		return lua_tostring(L, 1);
	else
		return lua_tostring(L, 2);

	SetLUA(false);
}

//Return Fullscreen Mode
bool LuaFuncs::GetFullscreen()
{
	SetLUA(true);

	lua_getglobal(L, "FULLSCREEN");

	return lua_toboolean(L, 1);

	SetLUA(false);
}

//True = WPOS_X, False = WPOS_Y
int LuaFuncs::GetWindowPos(bool mode)
{
	SetLUA(true);

	lua_getglobal(L, "WPOS_X");
	lua_getglobal(L, "WPOS_Y");

	if (mode)
		return (int)lua_tonumber(L, 1);
	else
		return (int)lua_tonumber(L, 2);

	SetLUA(false);
}

//Color Depth
int LuaFuncs::GetColorDepth()
{
	SetLUA(true);

	lua_getglobal(L, "COLORDEPTH");

		return (int)lua_tonumber(L, 1);

	SetLUA(false);
}