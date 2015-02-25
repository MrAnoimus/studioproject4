#include "Obstacle.h"


Obstacle::Obstacle(void)
{
}


Obstacle::~Obstacle(void)
{
}
void Obstacle::Init(Vector3D pos)
{
	LoadTGA(&IsBuilding, "Textures/Building/loading.tga");
	LoadTGA(&ObstacleTexture, "Textures/Building/badland.tga");
	SetSize(50);
	SetPosition(pos);
	SetBPercentage(0);
	SetCost(800);
	SetTier(0);
	this->rotationSpeed = 0.5f;
}
void Obstacle::Update()
{
	rotationSpeed++;
}

void Obstacle::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(GetPosition().x,GetPosition().y,GetPosition().z);
		if(GetTier() == 0)
		{
			glBindTexture(GL_TEXTURE_2D, ObstacleTexture.id);
		}
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(-GetSize(),GetSize());
				glTexCoord2f(0,1);
				glVertex2f(GetSize(),GetSize());
				glTexCoord2f(0,0);
				glVertex2f(GetSize(),-GetSize());
				glTexCoord2f(1,0);
				glVertex2f(-GetSize(),-GetSize());				
			glEnd();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glColor3f(1,1,1);
}
float Obstacle::GetRSpeed()
{
	return this->rotationSpeed;
}
void Obstacle::SetRspeed(float rs)
{
	this->rotationSpeed = rs;
}