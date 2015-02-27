#pragma once
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>       
#include <iostream>
#include "Resource.h"

#include <GL/glut.h>
#include "LoadTGA.h"

using namespace std;

class CRandomEvent:CResource
{
private:
	TextureImage EventTexture[10];
	
public:
	void HandleREvents(int type);
	int type;
	bool IsDisplay;
	void CreateEventz(int type);
	int Random();

	CResource resource;
	CRandomEvent(void);
	~CRandomEvent(void);
};

