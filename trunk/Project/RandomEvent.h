#pragma once
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>       
#include <iostream>
#include "Resource.h"

using namespace std;


	
class CRandomEvent
{
private:
	int type;

public:

	void CreateEventz();
	int Random();

	CResource resource;
	CRandomEvent(void);
	~CRandomEvent(void);
};

