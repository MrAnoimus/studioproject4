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
	this->Tag = "nothing";
	//building stuff
	this->Btype = 0;
	this->full = false;
	this->startdestory = false;
	myGaugeBar.init(1,0,1,this->Position);
	myHouse.Init(this->Position);
	myFCourt.Init(this->Position);
	myGstore.Init(this->Position);
	myShelter.Init(this->Position);
	myObstacle.Init(this->Position);
	myDebris.Init(this->Position);
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
			if(Selected)
			{
				this->Color.Set(0,1,0);//green
			}else
			{
				this->Color.Set(1,0,0);//red
			}
			
		}
		if(Type == UNBUILDABLE)
		{
			if(Selected)
			{
				this->Color.Set(0,1,0);//green
			}else
			{
				this->Color.Set(1,0,0);//red
			}
		}
		if(!ClickedOn && !Selected && Type != UNBUILDABLE)
		{
			this->Color.Set(1,1,1);//white
		}
	}else
	{//mode off

		if(!Empty)
		{
			startbuild= true;
		}
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
				case 4:
				{
					myGaugeBar.update(1.0f);
					myShelter.Update();
				}break;
				case 5:
				{
					myGaugeBar.update(0.5f);
					myObstacle.Update();
				}break;
				case 6:
				{
					myGaugeBar.update(0.5f);
					myDebris.Update();
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
		Vector3D temp(0,0,-3);
		DrawTileOutLine();
		DrawTile();
		switch(Btype)
		{
			case 1:
			{
				//set building speed
				myHouse.SetPosition(this->Position+temp);
				myHouse.SetAlpha(0.5f);
				myHouse.Draw();
			}break;
			case 2:
			{
				myFCourt.SetPosition(this->Position+temp);
				myFCourt.SetAlpha(0.5f);
				myFCourt.Draw();
			}break;
			case 3:
			{
				myGstore.SetPosition(this->Position+temp);
				myGstore.SetAlpha(0.5f);
				myGstore.Draw();
			}break;
			case 4:
			{
				myShelter.SetPosition(this->Position+temp);
				myShelter.SetAlpha(0.5f);
				myShelter.Draw();
			}break;
			case 5:
			{
				myObstacle.SetAlpha(0.5f);
				myObstacle.Draw();
			}break;
			case 6:
			{	
				myDebris.SetAlpha(0.5f);
				myDebris.Draw();
			}break;
		}
	}else
	{//mode off
		Vector3D temp(0,0,-3);
		if(ClickedOn)
		{
			if(!Empty)
			{
				//if not empty
				Vector3D temp2(50,-50,0);
				myGaugeBar.setPos(this->Position+temp2);
				if(myGaugeBar.getdone()==false)
				{
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
						case 4:
						{
							myShelter.SetPosition(this->Position+temp);
							myShelter.DrawBuildingbar(myShelter.GetRSpeed());
						}break;
						case 5:
						{
							//set building speed
							myObstacle.SetPosition(this->Position+temp);
							myObstacle.DrawDestructing(myObstacle.GetRSpeed());
						}break;
						case 6 :
						{
							myDebris.SetPosition(this->Position+temp);
							myDebris.DrawDestructing(myDebris.GetRSpeed());
						}break;
					}
					myGaugeBar.draw();
				}else
				{//bar 100%
					switch(Btype)
					{
						case 1:
						{
							myHouse.SetAlpha(1.0f);
							myHouse.Draw();
						}break;
						case 2:
						{
							myFCourt.SetAlpha(1.0f);
							myFCourt.Draw();
						}break;
						case 3:
						{
							myGstore.SetAlpha(1.0f);
							myGstore.Draw();
						}break;
						case 4:
						{
							myShelter.SetAlpha(1.0f);
							myShelter.Draw();
						}break;
						case 5:
						{
							if(Empty)
							{
								myObstacle.SetAlpha(1.0f);
								myObstacle.Draw();
							}else
							{
								Selected = false;
								ClickedOn = false;
								myGaugeBar.setDone(false);
								myGaugeBar.setPercentage(0);
								Empty = true;
							}
						}break;
						case 6:
						{
							if(Empty)
							{
								myDebris.SetAlpha(1.0f);
								myDebris.Draw();
							}else
							{
								Selected = false;
								ClickedOn = false;
								myGaugeBar.setDone(false);
								myGaugeBar.setPercentage(0);
								Empty = true;
							}
						}break;
					}
				}
			}
		}else
		{//not clicked on
			switch(Btype)
			{
				case 1:
				{
					myHouse.SetPosition(this->Position+temp);
					myHouse.Draw();
					ClickedOn = true;
					Empty = false;
				}break;
				case 2:
				{
					myFCourt.SetPosition(this->Position+temp);
					myFCourt.Draw();
					ClickedOn = true;
					Empty = false;
				}break;
				case 3:
				{
					myGstore.SetPosition(this->Position+temp);
					myGstore.Draw();
					ClickedOn = true;
					Empty = false;
				}break;
				case 4:
				{
					myShelter.SetPosition(this->Position+temp);
					myShelter.Draw();
					ClickedOn = true;
					Empty = false;
				}break;
				case 5:
				{
					myObstacle.SetAlpha(1.0f);
					myObstacle.SetPosition(this->Position+temp);
					myObstacle.Draw();
				}break;
				case 6:
				{
					myDebris.SetAlpha(1.0f);
					myDebris.SetPosition(this->Position+temp);
					myDebris.Draw();
				}break;
			}
		}
	}
}
bool Tile::GetFull()
{
	return full;
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
void Tile::SetFull(bool f)
{
	full = f;
}
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