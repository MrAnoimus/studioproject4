#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#pragma once
#include "vector3D.h"
#include <time.h>

struct GameObject
{
	enum GAMEOBJECT_TYPE 
	{
		GO_NONE = 0,	
		GO_COIN,
		GO_CATCHER,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3D pos;
	Vector3D vel;
	Vector3D scale;
	bool active;
	GameObject(GAMEOBJECT_TYPE typeValue = GO_COIN);
	~GameObject();

	

	

};



#endif