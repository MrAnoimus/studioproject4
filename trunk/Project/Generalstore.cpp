#include "Generalstore.h"


Generalstore::Generalstore(void)
{
}


Generalstore::~Generalstore(void)
{
}
void Generalstore::Init(Vector3D pos)
{
	LoadTGA(&IsBuilding, "Textures/Building/loading.tga");
	LoadTGA(&GStoreTexture, "Textures/Building/generalstore.tga");
	SetSize(50);
	SetPosition(pos);
	SetBPercentage(0);
	SetCost(600);
	SetTier(0);
	this->rotationSpeed = 0.4f;
	SetAlpha(1.0f);
}
void Generalstore::Update()
{
	rotationSpeed++;
}
void Generalstore::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1,1,1,GetAlpha());
		glTranslatef(GetPosition().x,GetPosition().y,GetPosition().z);
		if(GetTier() == 0)
		{
			glBindTexture(GL_TEXTURE_2D, GStoreTexture.id);
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

float Generalstore::GetRSpeed()
{
	return this->rotationSpeed;
}
void Generalstore::SetRspeed(float rs)
{
	this->rotationSpeed = rs;
}