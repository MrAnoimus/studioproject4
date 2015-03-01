#include "FoodCourt.h"


FoodCourt::FoodCourt(void)
{

}

FoodCourt::~FoodCourt(void)
{

}

void FoodCourt::Init(Vector3D pos)
{
	LoadTGA(&IsBuilding, "Textures/Building/loading.tga");
	LoadTGA(&FoodCourtTexture, "Textures/Building/foodcourt.tga");
	SetSize(50);
	SetPosition(pos);
	SetBPercentage(0);
	SetCost(300);
	SetMaintenanceFee(100);
	SetEarnings(200);
	SetTier(0);
	this->rotationSpeed = 0.5f;
	SetAlpha(1.0f);
}
void FoodCourt::Update()
{
	rotationSpeed++;
}

void FoodCourt::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1,1,1,GetAlpha());
		glTranslatef(GetPosition().x,GetPosition().y,GetPosition().z);
		if(GetTier() == 0)
		{
			glBindTexture(GL_TEXTURE_2D, FoodCourtTexture.id);
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
float FoodCourt::GetRSpeed()
{
	return this->rotationSpeed;
}
void FoodCourt::SetRspeed(float rs)
{
	this->rotationSpeed = rs;
}