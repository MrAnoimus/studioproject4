#pragma once
#include "freeType.h"
#include "LoadTGA.h"
#include "GameTime.h"

class GameUI
{
	private:
		//fonts
		freetype::font_data Time_Font;
		int size;
		int iconSize;
	public:
		TextureImage SelectionTexture[10];
		TextureImage Icon_MoneyTexture;
		TextureImage Icon_WorkerTexture;
		TextureImage Icon_PopulationTexture;
		TextureImage Icon_AngryTexture;
		TextureImage Icon_Homeless;
		CGameTime myGameTime;
		GameUI(void);
		~GameUI(void);
		void Init();
		void Update();
		void DrawResourceData(int x , int y,int money ,int population,int worker,int MaxWorker,int angrypeople , int homelesspeople);
		void DrawResource(int x , int y);
		void DrawSelect(int x , int y ,bool mode, int type);
		void Draw(float x , float y,std::string Bname,int cost,bool modeon);
		//get
		int GetIconSize();
		int GetSize();
		//set
};

