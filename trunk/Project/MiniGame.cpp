#include "MiniGame.h"

MiniGame::MiniGame(void)
	:AnimationCounter(0)
{
	glEnable(GL_TEXTURE_2D);
	LoadTGA(&coin, "Textures/MaleCitizen.tga");
	//for mini game
	minigame = false;
	gravity.Set(0, -9.8f, 0);
	fallspeed = 1;
	CposX = Math::RandIntMinMax(320, 780);
	CposY = 110;
	spawntime = 0;
}


MiniGame::~MiniGame(void)
{
}

void MiniGame::Update()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	static int ctime = glutGet(GLUT_ELAPSED_TIME);

	if (time - ctime > 300) 
	{
		this->AnimationCounter--;
		if (this->AnimationCounter == 0)
		{
			this->AnimationCounter = 2;
		}
		ctime = time;
	}

}

void MiniGame::SetAnimationCounter(int AnimationCounter)
{
	this->AnimationCounter=AnimationCounter;
}

int MiniGame::GetAnimationCounter(void)
{
	return this->AnimationCounter;
}

void MiniGame::RenderCoin(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, coin.id);
	glBegin(GL_QUADS);
		glTexCoord2f(/*0.125 * AnimationCounter*/1 , 1); 
		glVertex2f(10, 10);
		glTexCoord2f(/*0.125 * AnimationCounter*/1 , 0); 
		glVertex2f(10, 0);
		glTexCoord2f(/*0.125 * AnimationCounter*/1 + 0.25, 0);
		glVertex2f(0, 0);
		glTexCoord2f(/*0.125 * AnimationCounter*/1 + 0.25, 1);
		glVertex2f(0, 10);
	glEnd();
	glPopMatrix();
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

void MiniGame::DrawObject(GameObject *mg)
{
	//DRAW THIS STUFF IN THE MINIGAME CLASS PLEASE
	switch(mg->type)
	{
	case GameObject::GO_COIN:
		{
			//glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glColor3f(0,0,0);
			glTranslatef(mg->pos.x, mg->pos.y, mg->pos.z);
			glScalef(mg->scale.x, mg->scale.y, mg->scale.z);
			glutSolidSphere(10,32,32);
			glPopMatrix();
			//glDisable(GL_TEXTURE_2D);
		}
		break;
	case GameObject::GO_CATCHER:
		{
			//glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glColor3f(1,0,0);
			glTranslatef(mg->pos.x, mg->pos.y, mg->pos.z);
			glScalef(mg->scale.x, mg->scale.y, mg->scale.z);
			glutSolidSphere(10,32,32);
			glPopMatrix();
			//glDisable(GL_TEXTURE_2D);
		}
		break;
	}
}