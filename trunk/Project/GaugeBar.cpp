#include "GaugeBar.h"


GaugeBar::GaugeBar(void)
{
}


GaugeBar::~GaugeBar(void)
{
}

void GaugeBar::init(float r,float g,float b ,Vector3D pos)
{
	this->Position = pos;
	Percentage = 0;
	Height =10;
	Color.Set(r,g,b);
	done = false;
}

void GaugeBar::draw()
{
		//percentage is width
		//inner
		glPushMatrix();
			glTranslatef(Position.x, Position.y, Position.z+1);
			//glEnable( GL_TEXTURE_2D );
			//glEnable( GL_BLEND );
			glColor4f(Color.x, Color.y, Color.z, 0.7f);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(0,Height);
				glTexCoord2f(1,0);
				glVertex2f(-Percentage,Height);
				glTexCoord2f(1,1);
				glVertex2f(-Percentage,0);
				glTexCoord2f(0,1);
				glVertex2f(0,0);				
			glEnd();
			//glDisable( GL_BLEND );
			//glDisable( GL_TEXTURE_2D );
		glPopMatrix();

		//outline
		glPushMatrix();
			glLineWidth(4);
			glTranslatef(Position.x, Position.y, Position.z);
			//glEnable( GL_TEXTURE_2D );
			//glEnable( GL_BLEND );
			glColor4f(0, 0, 0, 1.0f);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_LINE_LOOP);
				glTexCoord2f(0,0);
				glVertex2f(0,Height);
				glTexCoord2f(1,0);
				glVertex2f(-100,Height);
				glTexCoord2f(1,1);
				glVertex2f(-100,0);
				glTexCoord2f(0,1);
				glVertex2f(0,0);				
			glEnd();
			//glDisable( GL_BLEND );
			//glDisable( GL_TEXTURE_2D );
		glPopMatrix();
		glColor3f(1,1,1);
}
void GaugeBar::update()
{

	Percentage+=1.0f;
	if(Percentage>=100)
	{
		Percentage=100;
		done = true;
	}
}
//get
bool GaugeBar::getdone()
{
	return this->done;
}
bool GaugeBar::getActive()
{
	return this->Active;
}

Vector3D GaugeBar::getPos()
{
	return Position;
}

Vector3D GaugeBar::getColor()
{
	return Color;
}
float GaugeBar::getPercentage()
{
	return Percentage;
}
//set
void GaugeBar::setDone(bool d)
{
	this->done = d;
}
void GaugeBar::setActive(bool at)
{
	this->Active = at;
}
void GaugeBar::setPos(Vector3D newpos)
{
	Position = newpos;
}
void GaugeBar::setColor(Vector3D newColor)
{
	Color = newColor;
}
void GaugeBar::setPercentage(float P)
{
	Percentage = P;
}