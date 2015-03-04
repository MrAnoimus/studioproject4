#include "GameUI.h"


GameUI::GameUI(void)
{

}

GameUI::~GameUI(void)
{
	
}

void GameUI::Init()
{
	Time_Font_small.init("Fonts/Anagram.TTF", 20);
	Time_Font.init("Fonts/Anagram.TTF", 42);

	LoadTGA(&SelectionTexture[0],"Textures/UI/Btype0.tga");
	LoadTGA(&SelectionTexture[1],"Textures/UI/Btype1.tga");
	LoadTGA(&SelectionTexture[2],"Textures/UI/Btype2.tga");
	LoadTGA(&SelectionTexture[3],"Textures/UI/Btype3.tga");
	LoadTGA(&SelectionTexture[4],"Textures/UI/Btype4.tga");
	LoadTGA(&SelectionTexture[5],"Textures/UI/Btype5.tga");

	LoadTGA(&Icon_MoneyTexture,"Textures/UI/money.tga");
	LoadTGA(&Icon_WorkerTexture,"Textures/UI/workerIcon.tga");
	LoadTGA(&Icon_PopulationTexture,"Textures/UI/population_Icon.tga");
	LoadTGA(&Icon_AngryTexture,"Textures/Enraged.tga");
	LoadTGA(&Icon_Homeless,"Textures/Building/shelter.tga");
	myGameTime.Init();
	this->size = 50;
	this->iconSize = 25;
}
void GameUI::Update()
{
	myGameTime.Update();
}
void GameUI::DrawResourceData(int x , int y,int money ,int population,int worker,int MaxWorker,int angrypeople , int homelesspeople)
{
	print(Time_Font,x+20,y,"$%d", money);
	print(Time_Font,x+20,y-100,"%d", population);
	print(Time_Font,x+20,y-200,"%d/%d", worker,MaxWorker);
	print(Time_Font,x+20,y-300,"%d", angrypeople);
	print(Time_Font,x+20,y-400,"%d", homelesspeople);
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

	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(x,y+180,0);
		glBindTexture(GL_TEXTURE_2D, Icon_AngryTexture.id);
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

	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(x,y+240,0);
		glBindTexture(GL_TEXTURE_2D, Icon_Homeless.id);
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
void GameUI::DrawSelectionInfo(int x , int y,std::string Bname,int cost,int earning,int fees,bool modeon)
{
	if(modeon)
	{
		print(Time_Font_small,x-225,y/2+50,"%s",Bname.c_str());
		print(Time_Font_small,x-225,y/2,"Cost:%d",cost);
		print(Time_Font_small,x-225,y/2-50,"Earning:%d",earning);
		print(Time_Font_small,x-225,y/2-100,"Fees:%d",fees);
	}
}
void GameUI::Draw(float x , float y)
{
	print(Time_Font,x,y,"Day : %02d ", myGameTime.GetDay());
	print(Time_Font,x+300,y,"TIME : %02d : %02d", myGameTime.GetHour(),myGameTime.GetMinute());
}

int GameUI::GetIconSize()
{
	return iconSize;
}

int GameUI::GetSize()
{
	return size;
}