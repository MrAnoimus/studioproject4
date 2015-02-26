#pragma once
#include "freeType.h"
#include "GameTime.h"

class GameUI
{
	private:
		//fonts
		freetype::font_data Time_Font;
		CGameTime myGameTime;
	public:
		GameUI(void);
		~GameUI(void);
		void Init();
		void Update();
		void Draw(float x , float y);
};

