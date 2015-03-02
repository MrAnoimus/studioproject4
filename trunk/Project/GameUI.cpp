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

	LoadTGA(&Icon_MoneyTexture,"Textures/UI/money.tga");
	LoadTGA(&Icon_WorkerTexture,"Textures/UI/workerIcon.tga");
	LoadTGA(&Icon_PopulationTexture,"Textures/UI/population_Icon.tga");
	myGameTime.Init();
	this->size = 50;
	this->iconSize = 25;
}
void GameUI::Update()
{
	myGameTime.Update();
}
void GameUI::DrawResourceData(int x , int y,int money ,int population,int worker,int MaxWorker)
{
	print(Time_Font,x,y,"$%d", money);
	print(Time_Font,x,y-80,"%d", population);
	print(Time_Font,x,y-160,"%d/%d", worker,MaxWorker);
}
void GameUI::DrawResource(int x , int y)
{
	//money
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(x,y,0);
		glBindTexture(GL_TEXTURE_2D, Icon_MoneyTexture.id);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(-iconSize,iconSize);
				glTexCoord2f(1,0);
				glVertex2f(iconSize,iconSize);
				glTexCoord2f(1,1);
				glVertex2f(iconSize,-iconSize);
				glTexCoord2f(0,1);
				glVertex2f(-iconSize,-iconSize);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	//citizen count
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(x,y+60,0);
		glBindTexture(GL_TEXTURE_2D, Icon_PopulationTexture.id);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(-iconSize,iconSize);
				glTexCoord2f(1,0);
				glVertex2f(iconSize,iconSize);
				glTexCoord2f(1,1);
				glVertex2f(iconSize,-iconSize);
				glTexCoord2f(0,1);
				glVertex2f(-iconSize,-iconSize);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	//man power
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(x,y+120,0);
		glBindTexture(GL_TEXTURE_2D, Icon_WorkerTexture.id);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(-iconSize,iconSize);
				glTexCoord2f(1,0);
				glVertex2f(iconSize,iconSize);
				glTexCoord2f(1,1);
				glVertex2f(iconSize,-iconSize);
				glTexCoord2f(0,1);
				glVertex2f(-iconSize,-iconSize);
			glEnd();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
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
				case 6:
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
	print(Time_Font,x,y,"Day : %02d", myGameTime.GetDay());
	print(Time_Font,x,y-100,"%02d : %02d", myGameTime.GetHour(),myGameTime.GetMinute());//,myGameTime.GetTimeFrame().c_str());
}

int GameUI::GetIconSize()
{
	return iconSize;
}

int GameUI::GetSize()
{
	return size;
}