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
	LoadTGA(&IsDestructing, "Textures/Building/pixaxe.tga");
	LoadTGA(&ObstacleTexture, "Textures/Building/badland.tga");
	LoadTGA(&debrisTexture, "Textures/Building/debris.tga");

	SetSize(50);
	SetPosition(pos);
	SetBPercentage(0);
	SetCost(250);
	SetMaintenanceFee(0);
	SetEarnings(0);
	SetTier(0);
	this->rotationSpeed = 0.5f;
	SetAlpha(1.0f);
	test = true;
	diff = true;
}
void Obstacle::Update()
{
	if(test)
	{
		rotationSpeed--;
		if(rotationSpeed<=-45)
		{
			test= false;
		}
	}
	if(!test)
	{
		rotationSpeed++;
		if(rotationSpeed>=0)
		{
			test = true;
		}
	}
}

void Obstacle::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1,1,1,GetAlpha());
		glTranslatef(GetPosition().x,GetPosition().y,GetPosition().z);
		//badland
		if(diff)
		{
			glBindTexture(GL_TEXTURE_2D, ObstacleTexture.id);
		}else
		{
			glBindTexture(GL_TEXTURE_2D, debrisTexture.id);
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
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_TEST);
	glColor3f(1,1,1);
}
float Obstacle::GetRSpeed()
{
	return this->rotationSpeed;
}
bool Obstacle::GetDiff()
{
	return this->diff;
}

void Obstacle::SetDiff(bool d)
{
	this->diff = d;
}

void Obstacle::SetRspeed(float rs)
{
	this->rotationSpeed = rs;
}