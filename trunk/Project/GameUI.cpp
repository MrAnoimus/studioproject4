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
	LoadTGA(&SelectionTexture[0],"Textures/UI/Btype0.tga");
	LoadTGA(&SelectionTexture[1],"Textures/UI/Btype1.tga");
	LoadTGA(&SelectionTexture[2],"Textures/UI/Btype2.tga");
	LoadTGA(&SelectionTexture[3],"Textures/UI/Btype3.tga");
	LoadTGA(&SelectionTexture[4],"Textures/UI/Btype4.tga");
	LoadTGA(&SelectionTexture[5],"Textures/UI/Btype5.tga");
	myGameTime.Init();
	this->size = 50;
}
void GameUI::Update()
{
	myGameTime.Update();
}
void GameUI::DrawSelect(int x , int y ,bool mode , int type)
{
	if(mode)
	{
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTranslatef(x,y,0);
			switch(type)
			{
				case 0:
				{
					glBindTexture(GL_TEXTURE_2D, SelectionTexture[0].id);
				}break;
				case 1 :
				{
					glBindTexture(GL_TEXTURE_2D, SelectionTexture[1].id);
				}break;
				case 2 :
				{
					glBindTexture(GL_TEXTURE_2D, SelectionTexture[2].id);
				}break;
				case 3 :
				{
					glBindTexture(GL_TEXTURE_2D, SelectionTexture[3].id);
				}break;
				case 4:
				{
					glBindTexture(GL_TEXTURE_2D, SelectionTexture[4].id);
				}break;
				case 5:
				{
					glBindTexture(GL_TEXTURE_2D, SelectionTexture[5].id);
				}break;
			}
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0);
					glVertex2f(-50,50);
					glTexCoord2f(1,0);
					glVertex2f(50,50);
					glTexCoord2f(1,1);
					glVertex2f(50,-50);
					glTexCoord2f(0,1);
					glVertex2f(-50,-50);				
				glEnd();
			glPopMatrix();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	}
}
void GameUI::Draw(float x , float y)
{
	print(Time_Font,x,y,"Day : %d", myGameTime.GetDay());
	print(Time_Font,x,y-100,"%d : %d %s", myGameTime.GetHour(),myGameTime.GetMinute(),myGameTime.GetTimeFrame().c_str());
}