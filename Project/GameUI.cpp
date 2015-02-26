#include "GameUI.h"


GameUI::GameUI(void)
{

}

GameUI::~GameUI(void)
{
	
}

void GameUI::Init()
{
	Time_Font.init("Fonts/trsmillionrg.TTF", 42);
	myGameTime.Init();
}
void GameUI::Update()
{
	myGameTime.Update();
}

void GameUI::Draw(float x , float y)
{
	print(Time_Font,x,y,"Day : %d", myGameTime.GetDay());
}