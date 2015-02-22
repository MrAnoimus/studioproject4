#ifndef LUA_FUNCS_H
#define LUA_FUNCS_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <string>
using namespace std;

class LuaFuncs
{
public:

	static LuaFuncs *instance;
	lua_State *L;

	LuaFuncs();
	~LuaFuncs() {};

	static LuaFuncs *getInstance();

	//Set Up LUA
	void SetLUA(bool mode);

	//Screen Width & Height
	int GetScreen(bool mode);

	//Program Name and Version
	string GetName(bool mode);

	//Fullscreen
	bool GetFullscreen();

	//Window Position
	int GetWindowPos(bool mode);

	//Color Depth
	int GetColorDepth();

};

#endif