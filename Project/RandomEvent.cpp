#include "RandomEvent.h"

CRandomEvent::CRandomEvent(void)
{
	IsDisplay = false;
	
}


CRandomEvent::~CRandomEvent(void)
{
}

int CRandomEvent::Random()
{
	int i = rand()% 5;
	type = i;
	return type;
}

void CRandomEvent::CreateEventz(int typez)
{
	switch (typez)
	{
	case 0:
		{
			resource.SetMoney(resource.GetMoney() -10);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		}
		break;
	case 1:
		{
			resource.SetMoney(resource.GetMoney() -10);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		}

		break;
	case 2:
		{
			resource.SetMoney(resource.GetMoney() +10);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		}
		break;
	case 3:
		{
			resource.SetManpower(resource.GetManPower() +10);
			cout <<"The Amount of Man Power is "<<resource.GetManPower()<<"\n";
		}
		break;
	case 4:
		{
			resource.SetManpower(resource.GetManPower() +10);
			cout <<"The Amount of Man Power is "<<resource.GetManPower()<<"\n";
		}
		break;

	default:
		resource.SetMoney(resource.GetMoney() -10);
			cout <<"The Amount of money is "<<resource.GetMoney()<<"\n";
		break;
	}
}

void CRandomEvent::HandleREvents(int type)
{
	LoadTGA(&EventTexture[0],"Textures/bad1.tga");
	LoadTGA(&EventTexture[1],"Textures/bad2.tga");
	LoadTGA(&EventTexture[5],"Textures/good1.tga");
	LoadTGA(&EventTexture[6],"Textures/good2.tga");
	LoadTGA(&EventTexture[7],"Textures/good3.tga");

	switch (type)
	{
		// - money
	case 0:
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[0].id);
			glPushMatrix();
				glTranslatef(100,50,0);
				glScalef(0.75,0.75,0.75);
				glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,600);
				glTexCoord2f(0,1);
				glVertex2f(800,600);
				glTexCoord2f(0,0);
				glVertex2f(800,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		break;
	case 1:
		// - money
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[1].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
				glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,600);
				glTexCoord2f(0,1);
				glVertex2f(800,600);
				glTexCoord2f(0,0);
				glVertex2f(800,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		break;
	case 2:
		// + money
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[5].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
				glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,600);
				glTexCoord2f(0,1);
				glVertex2f(800,600);
				glTexCoord2f(0,0);
				glVertex2f(800,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		break;
	case 3:	
		// + Man power
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[6].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
				glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,600);
				glTexCoord2f(0,1);
				glVertex2f(800,600);
				glTexCoord2f(0,0);
				glVertex2f(800,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		break;
	case 4:
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, EventTexture[7].id);
			glPushMatrix();
				glTranslatef(100,50,-1);
				glScalef(0.75,0.75,0.75);
				glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,600);
				glTexCoord2f(0,1);
				glVertex2f(800,600);
				glTexCoord2f(0,0);
				glVertex2f(800,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		break;
	}
	
}