#pragma once
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>       
#include <iostream>
#include "Resource.h"

using namespace std;

class CRandomEvent:CResource
{
private:
	
	
public:
	int type;
	bool IsDisplay;
	void CreateEventz(int type);
	int Random();

	CResource resource;
	CRandomEvent(void);
	~CRandomEvent(void);
};

