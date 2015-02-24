#include "ButtonClass.h"
//#include "Sound.h"

//Constructor
ButtonClass::ButtonClass() 
	: buttonhover(false)
	, buttonclicked(buttonhover)
	, buttonsfx(buttonclicked)
{
	//Initialise Region to out-of-screen
	areaposX.Set(-50,0);
	areaposY = areaposX = areaposY = areaposX;

	//This is our current screen resolution
	//(non-fullscreen)
	scrResolution.Set(800, 600);



}

//Destructor
ButtonClass::~ButtonClass() {}

//Set Region
void ButtonClass::Set(int x1, int x2, int y1, int y2)
{
	//Using a ratio would make the region dynamic
	areaposX.Set((float)(glutGet(GLUT_WINDOW_WIDTH)/(scrResolution.x/x1)),
				   (float)(glutGet(GLUT_WINDOW_WIDTH)/(scrResolution.x/x2)));
	areaposY.Set((float)(glutGet(GLUT_WINDOW_HEIGHT)/(scrResolution.y/y1)),
				   (float)(glutGet(GLUT_WINDOW_HEIGHT)/(scrResolution.y/y2)));

	//Set dynamic render region
	renderposX.Set((float)(SCREENWIDTH/(scrResolution.x/x1)),
				   (float)(SCREENWIDTH/(scrResolution.x/x2)));
	renderposY.Set((float)(SCREENHEIGHT/(scrResolution.y/y1)), 
				   (float)(SCREENHEIGHT/(scrResolution.y/y2)));
}

//Update Mouse Move
void ButtonClass::UpdateMouseMove(int x, int y)
{
	//Check if mouse is within Region
	if (x > areaposX.x && x < areaposX.y &&
		y > areaposY.x && y < areaposY.y)
		//Set buttonhover to true if mouse is within Region
		buttonhover = true;
	else
		//Set buttonhover to false if mouse is not within Region
		buttonhover = buttonsfx = false;

	//if (buttonhover && !buttonsfx)
	//{
	//	//Play buttonhover Sound
	//	CSound::getInstance()->PlayMusic(CSound::SOUND_buttonhover, false, false);

	//	//Play Sound Only Once
	//	buttonsfx = true;
	//}
}

//Render Button
void ButtonClass::Render()
{
	glEnable(GL_TEXTURE_2D);

	float w = renderposX.y-renderposX.x;
	float h = renderposY.y-renderposY.x;

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 1, 1, 1);
	glTranslatef(renderposX.x, renderposY.x, 0);

		//Mouse is buttonhovering over Button
		if (buttonhover)
			glBindTexture(GL_TEXTURE_2D, button[1].id);
		//Mouse is not buttonhovering over Button
		else
			glBindTexture(GL_TEXTURE_2D, button[0].id);

		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex2f(0, h);
				glTexCoord2f(1,0); glVertex2f(w, h);
				glTexCoord2f(1,1); glVertex2f(w, 0);
				glTexCoord2f(0,1); glVertex2f(0, 0);				
			glEnd();
		glPopMatrix();

	glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}