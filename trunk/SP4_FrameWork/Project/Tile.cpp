#include "Tile.h"


Tile::Tile(void)
{

}


Tile::~Tile(void)
{

}

void Tile::Init()
{
	this->Position.Set(50,50,-1);
	this->Color.Set(1,0,0);
	this->Alpha = 1;
	this->Size = 50;
}
void Tile::Update()
{

}
void Tile::Draw(float x , float y)
{
	//glEnable(GL_TEXTURE_2D);
	//black outline
	glPushMatrix();
		glPushMatrix();
			glLineWidth(2);
			glTranslatef(x,y,this->Position.z);
			glColor4f(0, 0, 0, 1.0f);
			glBegin(GL_LINE_LOOP);
				glTexCoord2f(0,0);
				glVertex2f(-Size,Size);
				glTexCoord2f(1,0);
				glVertex2f(Size,Size);
				glTexCoord2f(1,1);
				glVertex2f(Size,-Size);
				glTexCoord2f(0,1);
				glVertex2f(-Size,-Size);				
			glEnd();
		glPopMatrix();
	glPopMatrix();
		//quad
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
			glTranslatef(x,y,this->Position.z);
			glColor4f(this->Color.x,this->Color.y,this->Color.z,Alpha);
			//glBindTexture (GL_TEXTURE_2D, TileTexture.texID);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(-Size,Size);
				glTexCoord2f(1,0);
				glVertex2f(Size,Size);
				glTexCoord2f(1,1);
				glVertex2f(Size,-Size);
				glTexCoord2f(0,1);
				glVertex2f(-Size,-Size);			
			glEnd();
		glPopMatrix();
	glPopMatrix();
	glColor3f(1,1,1);
	//glDisable(GL_TEXTURE_2D);
}

int Tile::GetType()
{
	return Type;
}
bool Tile::GetEmpty()
{
	return Type;
}
Vector3D Tile::GetPosition()
{
	return Position;
}
Vector3D Tile::GetColor()
{
	return Color;
}

void Tile::SetType(int type)
{
	Type = type;
}
void Tile::SetEmpty(bool e)
{
	Empty = e;
}
void Tile::SetPosition(Vector3D pos)
{
	Position = pos;
}
void Tile::SetColor(Vector3D c)
{
	Color = c;
}