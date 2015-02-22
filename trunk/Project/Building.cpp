#include "Building.h"


Building::Building(void)
: Size(50),Cost(100.0f)
{

}

Building::~Building(void)
{
}

void Building::Init(Vector3D pos)
{
	LoadTGA(&Building1, "Textures/Building/building1.tga");
	this->Size = 50;
	this->Position = pos;
	this->Cost = 100.0f;
}
void Building::Update()
{

}
void Building::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTranslatef(this->Position.x,this->Position.y,this->Position.z);
		glBindTexture(GL_TEXTURE_2D, Building1.id);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(-Size,Size);
				glTexCoord2f(0,1);
				glVertex2f(Size,Size);
				glTexCoord2f(0,0);
				glVertex2f(Size,-Size);
				glTexCoord2f(1,0);
				glVertex2f(-Size,-Size);				
			glEnd();
		glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}
float Building::GetCost()
{
	return this->Cost;
}
Vector3D Building::GetPosition()
{
	return this->Position;
}
void Building::SetPosition(Vector3D pos)
{
	this->Position = pos;
}