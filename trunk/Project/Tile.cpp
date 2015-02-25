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
	this->startdestory = false;
	myGaugeBar.init(1,0,1,this->Position);
	myHouse.Init(this->Position);
	myFCourt.Init(this->Position);
	myGstore.Init(this->Position);
	myObstacle.Init(this->Position);
}
void Tile::Update()
{
	//myHouse.Update();
	if(ModeOn)
	{
		if(Selected)
		{
			this->Color.Set(0,1,0);//green
		}
		if(ClickedOn)
		{
			//check which building the player want
			if(!Empty)
			{
				startbuild= true;
			}
			
			this->Color.Set(1,1,0);//yellow
		}
		if(Type == UNBUILDABLE)
		{
			this->Color.Set(1,0,0);//red
		}
		if(!ClickedOn && !Selected && Type != UNBUILDABLE)
		{
			this->Color.Set(1,1,1);//white
		}
	}else
	{
		if(ClickedOn)
		{
			if(!Empty)
			{
				startbuild= true;
			}
		}
		/*
			if(Btype == 5)
			{
				myGaugeBar.update(1.0f);
				myObstacle.Update();
			}*/
		if(startbuild)
		{
			switch(Btype)
			{
				case 1:
				{
					myGaugeBar.update(1.0f);
					myHouse.Update();
				}break;
				case 2:
				{
					myGaugeBar.update(0.5f);
					myFCourt.Update();
				}break;
				case 3:
				{
					myGaugeBar.update(0.5f);
					myGstore.Update();
				}break;
				case 5:
				{
					myGaugeBar.update(0.5f);
					myObstacle.Update();
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
		if(ClickedOn)
		{
			if(!Empty)
			{
				if(Btype != 0)
				{
					ClickedOn = true;
				}
			}
		}
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
							//set building speed
							myHouse.SetPosition(this->Position+temp);
							myHouse.DrawBuildingbar(myHouse.GetRSpeed());
						}break;
						case 2:
						{
							//set building speed
							myFCourt.SetPosition(this->Position+temp);
							myFCourt.DrawBuildingbar(myFCourt.GetRSpeed());
						}break;
						case 3:
						{
							//set building speed
							myGstore.SetPosition(this->Position+temp);
							myGstore.DrawBuildingbar(myGstore.GetRSpeed());
						}break;
						case 5:
						{
							//set building speed
							myObstacle.SetPosition(this->Position+temp);
							myObstacle.DrawBuildingbar(myObstacle.GetRSpeed());
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
						case 3:
						{
							myGstore.Draw();
						}break;
						case 5:
						{
							if(Empty)
							{
								myObstacle.Draw();
							}else
							{
								Selected = false;
								ClickedOn = false;
								Empty = false;
								myGaugeBar.setDone(false);
								myGaugeBar.setPercentage(0);
							}
						}break;
					}
				}
			}
		}else
		{
			if(Btype == 1)
			{
				Vector3D temp;
				temp.Set(0,0,-3);
				myHouse.SetPosition(this->Position+temp);
				myHouse.Draw();
				ClickedOn = true;
				Empty = false;
			}
			if(Btype == 2)
			{
				Vector3D temp;
				temp.Set(0,0,-3);
				myFCourt.SetPosition(this->Position+temp);
				myFCourt.Draw();
				ClickedOn = true;
				Empty = false;
			}
			if(Btype == 3)
			{
				Vector3D temp;
				temp.Set(0,0,-3);
				myGstore.SetPosition(this->Position+temp);
				myGstore.Draw();
				ClickedOn = true;
				Empty = false;
			}
			if(Btype == 5)
			{
				Vector3D temp;
				temp.Set(0,0,-3);
				myObstacle.SetPosition(this->Position+temp);
				myObstacle.Draw();
				//Empty = true;
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
void Tile::SetSize(int sz)
{
	Size = sz;
}
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