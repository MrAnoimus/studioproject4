#include "Building.h"


Building::Building(void)
: Size(50),Cost(0)
{
}

Building::~Building(void)
{
	
}
void Building::DrawBuildingbar(float r)
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(GetPosition().x,GetPosition().y,GetPosition().z);
		glBindTexture(GL_TEXTURE_2D, IsBuilding.id);
		glRotatef(r,0,0,1);
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
}

//getter
float Building::GetAlpha()
{
	return this->Alpha;
}
int Building::GetTier()
{
	return this->Tier;
}

float Building::GetBPercentage()
{
	return this->BuildPercentage;
}
int Building::GetSize()
{
	return this->Size;
}
float Building::GetCost()
{
	return this->Cost;
}
Vector3D Building::GetPosition()
{
	return this->Position;
}
//setter
void Building::SetAlpha(float a)
{
	this->Alpha = a;
}
void Building::SetTier(int t)
{
	this->Tier = t;
}
void Building::SetCost(float c)
{
	this->Cost = c;
}
void Building::SetBPercentage(float pc)
{
	this->BuildPercentage = pc;
}
void Building::SetSize(int size)
{
	this->Size = size;
}
void Building::SetPosition(Vector3D pos)
{
	this->Position = pos;
}