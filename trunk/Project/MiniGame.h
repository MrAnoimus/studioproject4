#pragma once
#include "LoadTGA.h"
#include <time.h>

using namespace std;

class MiniGame
{
private:
	

public:
	MiniGame(void);
	~MiniGame(void);

	void Update();

	int AnimationCounter;

	void SetAnimationCounter(int AnimationCounter);
	int GetAnimationCounter(void);
	void RenderCoin();

	TextureImage coin;

};

