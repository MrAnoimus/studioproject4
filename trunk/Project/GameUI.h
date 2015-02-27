#pragma once
#include "freeType.h"
#include "LoadTGA.h"
#include "GameTime.h"

class GameUI
{
	private:
		//fonts
		freetype::font_data Time_Font;
		CGameTime myGameTime;
		int size;
	public:
		TextureImage SelectionTexture[3];
		GameUI(void);
		~GameUI(void);
		void Init();
		void Update();
		void DrawSelect(int x , int y ,bool mode, int type);
		void Draw(float x , float y);
};

