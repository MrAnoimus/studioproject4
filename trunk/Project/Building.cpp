#include "Building.h"


Building::Building(void)
: Size(50)
{

}

Building::~Building(void)
{
}

void Building::Init()
{
	LoadTGA(&Building1, "Textures/Building/building1.tga");
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

Vector3D Building::GetPosition()
{
	return this->Position;
}
void Building::SetPosition(Vector3D pos)
{
	this->Position = pos;
}