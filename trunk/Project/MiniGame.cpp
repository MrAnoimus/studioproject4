#include "MiniGame.h"

MiniGame::MiniGame(void)
{	
	//for mini game
	minigame = false;
	gravity.Set(0, -9.8f, 0);
	fallspeed = 1;
	CposX = Math::RandIntMinMax(320, 780);
	CposY = 110;
	spawntime = 0;

	//animation
	mgctr = 0, mgctr2 = 0;
	inverted = true;
}


MiniGame::~MiniGame(void)
{
}

void MiniGame::Update()
{
}


void MiniGame::DrawMGBG()
{
	//DRAW THIS STUFF IN THE MINIGAME CLASS PLEASE

	/*glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
		glColor3f(0.5,0.5,0.5);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,500);
				glTexCoord2f(0,1);
				glVertex2f(500,500);
				glTexCoord2f(0,0);
				glVertex2f(500,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glColor3f(1,1,1);
		/*glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);*/
}

void MiniGame::DrawTextureBase()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.125 * mgctr , 1);glVertex2f(30, 30);
		glTexCoord2f(0.125 * mgctr , 0);glVertex2f(30, 0);
		glTexCoord2f(0.125 * mgctr + 0.125, 0);glVertex2f(0, 0);
		glTexCoord2f(0.125 * mgctr + 0.125, 1);glVertex2f(0, 30);
	glEnd();

}

void MiniGame::DrawTextureBaseNotInvert()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 1);glVertex2f(60, 60);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 0);glVertex2f(60, 0);
		glTexCoord2f(0.125 * mgctr2, 0);glVertex2f(0,0);
		glTexCoord2f(0.125 * mgctr2, 1);glVertex2f(0, 60);
	glEnd();
}

void MiniGame::DrawTextureBaseInvert()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.125 * mgctr2 , 1);glVertex2f(60, 60);
		glTexCoord2f(0.125 * mgctr2 , 0);glVertex2f(60, 0);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 0);glVertex2f(0, 0);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 1);glVertex2f(0, 60);
	glEnd();
}

void MiniGame::DrawObject(GameObject *mg, const GLuint Texture)
{
	switch(mg->type)
	{
	case GameObject::GO_COIN:
		{
			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, Texture);
			glPushMatrix();
			glTranslatef(mg->pos.x, mg->pos.y, mg->pos.z);
			glScalef(mg->scale.x, mg->scale.y, mg->scale.z);
			DrawTextureBase();
			glPopMatrix();
			glDisable(GL_BLEND);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
		break;
	case GameObject::GO_CATCHER:
		{
			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glEnable(GL_BLEND); 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, Texture);
			glPushMatrix();
			glTranslatef(mg->pos.x, mg->pos.y, mg->pos.z);
			glScalef(mg->scale.x, mg->scale.y, mg->scale.z);

			if(!inverted)
			{
				DrawTextureBaseNotInvert();
			}
			else
			{
				DrawTextureBaseInvert();
			}

			glPopMatrix();
			glDisable(GL_BLEND);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);

		}
		break;
	}
}