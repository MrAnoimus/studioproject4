#include "House.h"


House::House(void)
{

}

House::~House(void)
{

}

void House::Init(Vector3D pos)
{
	LoadTGA(&IsBuilding, "Textures/Building/loading.tga");
	LoadTGA(&HouseTexture, "Textures/Building/House.tga");
	SetSize(50);
	SetPosition(pos);
	SetBPercentage(0);
	SetCost(500);
	SetTier(0);
	this->rotationSpeed = 1.0f;
}
void House::Update()
{
	rotationSpeed++;
}
void House::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(GetPosition().x,GetPosition().y,GetPosition().z);
		if(GetTier() == 0)
		{
			glBindTexture(GL_TEXTURE_2D, HouseTexture.id);
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

float House::GetRSpeed()
{
	return this->rotationSpeed;
}
void House::SetRspeed(float rs)
{
	this->rotationSpeed = rs;
}