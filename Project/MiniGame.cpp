#include "MiniGame.h"

MiniGame::MiniGame(void)
	:AnimationCounter(0)
{
	glEnable(GL_TEXTURE_2D);
	LoadTGA(&coin, "Textures/MaleCitizen.tga");
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