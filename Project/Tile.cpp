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
	this->ModeOn = false;
	this->startbuild = false;
	//building stuff
	this->Btype = 0;
	myGaugeBar.init(1,0,1,this->Position);
	myHouse.Init(this->Position);
	myFCourt.Init(this->Position);
}
void Tile::Update()
{
	//myHouse.Update();
	if(ModeOn)
	{
		if(Selected)
		{
			this->Color.Set(0,1,0);
		}
		if(ClickedOn)
		{
			//check which building the player want
			startbuild= true;
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
	}else
	{
		if(startbuild)
		{
			myGaugeBar.update();
			switch(Btype)
			{
				case 1:
				{
					myHouse.Update();
				}break;
				case 2:
				{
					myFCourt.Update();
				}break;
			}
		}
	}
}


//draw stuff
void Tile::DrawTileOutLine()
{
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
}
void Tile::DrawTile()
{
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
			glTranslatef(this->Position.x,this->Position.y,this->Position.z);
			glColor4f(this->Color.x,this->Color.y,this->Color.z,Alpha);
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
}
void Tile::Draw()
{
	if(ModeOn)
	{
		DrawTileOutLine();
		DrawTile();
	}else
	{
		if(ClickedOn)
		{
			if(!Empty)
			{
				//if not empty
				Vector3D temp,temp2;
				temp.Set(0,0,-3);
				temp2.Set(50,50,-4);

				myGaugeBar.setPos(this->Position+temp2);
				if(myGaugeBar.getdone()==false)
				{
					myGaugeBar.draw();
					switch(Btype)
					{
						case 1:
						{
							myHouse.SetPosition(this->Position+temp);
							myHouse.DrawBuildingbar();
						}break;
						case 2:
						{
							myFCourt.SetPosition(this->Position+temp);
							myFCourt.DrawBuildingbar();
						}break;
					}
				}else
				{
					switch(Btype)
					{
						case 1:
						{
							myHouse.Draw();
						}break;
						case 2:
						{
							myFCourt.Draw();
						}break;

					}
				}
			}
		}
	}
	
}



int Tile::GetBtype()
{
	return Btype;
}
bool Tile::GetModeOn()
{
	return ModeOn;
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

//setter

void Tile::SetBtype(int t)
{
	Btype = t;
}
void Tile::SetModeOn(bool m)
{
	ModeOn = m;
}
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