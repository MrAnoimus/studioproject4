#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "LuaFuncs.h"

//Screen Resolution
#define SCREENWIDTH LuaFuncs::getInstance()->GetScreen(true)
#define SCREENHEIGHT LuaFuncs::getInstance()->GetScreen(false)

//Program Name & Version
#define PROGRAM_NAME LuaFuncs::getInstance()->GetName(true)
#define PROGRAM_VERSION LuaFuncs::getInstance()->GetName(false)

//Fullscreen
#define FULLSCREEN LuaFuncs::getInstance()->GetFullscreen()

//Window Position
#define WPOS_X LuaFuncs::getInstance()->GetWindowPos(true)
#define WPOS_Y LuaFuncs::getInstance()->GetWindowPos(false)

//Window Position
#define COLORDEPTH LuaFuncs::getInstance()->GetColorDepth()

//int glutScreenX = glutGet(GL_WINDOW_WIDTH);
//int glutScreenY = glutGet(GL_WINDOW_HEIGHT);


#endif