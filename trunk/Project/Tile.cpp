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
	this->Color.Set(1,1,1);
	this->Alpha = 0.5f;
	this->Size = 50;
	this->Type = 0;
	this->Empty = true;
	this->ClickedOn = false;
}
void Tile::Update()
{
	if(Selected)
	{
		this->Color.Set(0,1,0);
	}
	if(ClickedOn)
	{
		this->Color.Set(1,1,0);
	}
	if(Type == UNBUILDABLE)
	{
		this->Color.Set(1,0,0);
	}
	if(!ClickedOn && !Selected && Type != UNBUILDABLE)
	{
		this->Color.Set(1,1,1);
	}
}
void Tile::Draw()
{
	//glEnable(GL_TEXTURE_2D);
	//black outline
	glPushMatrix();
		glPushMatrix();
			glLineWidth(2);
			glTranslatef(this->Position.x,this->Position.y,this->Position.z);
			glPushMatrix();
			glutSolidSphere(20,20,20);
			glPopMatrix();
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
			glTranslatef(this->Position.x,this->Position.y,this->Position.z);
			glColor4f(this->Color.x,this->Color.y,this->Color.z,Alpha);
			//switch(Type)
			//{
			//	case GRASS:
			//	{
			//		//glBindTexture (GL_TEXTURE_2D, TileTexture.texID);
			//	}break;
			//	case SOIL:
			//	{
			//		//glBindTexture (GL_TEXTURE_2D, TileTexture.texID);
			//	}break;
			//	case ROCK:
			//	{
			//		//glBindTexture (GL_TEXTURE_2D, TileTexture.texID);
			//	}break;
			//	case BAD:
			//	{
			//		//glBindTexture (GL_TEXTURE_2D, TileTexture.texID);
			//	}break;
			//}
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

bool Tile::IsClickedOn()
{
	return ClickedOn;
}
bool Tile::IsSelected()
{
	return Selected;
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
Vector3D Tile::GetCenterPoint(void)
{
	return NULL;
	//return Vector3D(x,y,z);
}

//setter
void Tile::SetIsClickedOn(bool co )
{
	ClickedOn = co;
}

void Tile::SetIsSelected(bool s )
{
	Selected = s;
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