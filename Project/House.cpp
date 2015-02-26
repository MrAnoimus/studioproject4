#include "House.h"


House::House(void)
{
	Owner= "Hi";
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
	this->deleted = false;
	this->rotationSpeed = 1.0f;
}
void House::Update()
{
	rotationSpeed++;
	if(deleted)
	{
		SetBPercentage(0);
		this->Owner = "NOBODY";
	}
}
void House::Draw()
{
	if(!deleted)
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
	
}
bool House::GetDeleted()
{
	return this->deleted;
}
float House::GetRSpeed()
{
	return this->rotationSpeed;
}
std::string House::GetOwner(void)
{
	return this->Owner;
}

void House::SetRspeed(float rs)
{
	this->rotationSpeed = rs;
}

void House::SetDeleted(bool d)
{
	this->deleted = d;
}

void House::SetOwner(std::string name)
{
	this->Owner = name;
}