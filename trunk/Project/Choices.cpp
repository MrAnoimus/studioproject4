#include "Choices.h"


Choices::Choices(void)
	:choice1(false),choice2(false),
	selected(false),popup(false),
	NumOfChoice(1)
{
	LoadTGA(&ChoiceBG[0],"Textures/ChoiceBG.tga");
	LoadTGA(&ChoiceBG[1],"Textures/ChoiceBG2.tga");
	LoadTGA(&ChoiceBG[2],"Textures/ChoiceBG3.tga");
	LoadTGA(&ChoiceBG[3],"Textures/ChoiceBG4.tga");
	LoadTGA(&ChoiceBG[4],"Textures/ChoiceBG5.tga");

	LoadTGA(&Choice1[0],"Textures/CheapTree.tga");
	LoadTGA(&Choice2[0], "Textures/ExpensiveTree.tga");
	our_font.init("Fonts/FFF_Tusj.TTF", 22);
}


Choices::~Choices(void)
{

}

int Choices::GetNumOfChoice(void)
{
	return NumOfChoice;
}


void Choices::SetNumOfChoice(int Choice)
{
	this->NumOfChoice= Choice;
}

void Choices::Draw(int type)
{
	if(popup==true)
	{
	int Size=275;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,ChoiceBG[type].id);
	glPushMatrix();
		glTranslatef(400,300,0);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0);
			glVertex2f(-Size*1.5,Size);
			glTexCoord2f(1,0);
			glVertex2f(Size*1.5,Size);
			glTexCoord2f(1,1);
			glVertex2f(Size*1.5,-Size);
			glTexCoord2f(0,1);
			glVertex2f(-Size*1.5,-Size);				
		glEnd();
	glPopMatrix();
	
	//if(NumOfChoice==1)
	//{
	//	glBindTexture(GL_TEXTURE_2D, CheapTree.id);
	//	glPushMatrix();
	//	glTranslatef(200,500,0);
	//		glBegin(GL_QUADS);
	//			glTexCoord2f(0,0);
	//			glVertex2f(-Size*0.49,Size*0.09);
	//			glTexCoord2f(1,0);
	//			glVertex2f(Size*0.49,Size*0.09);
	//			glTexCoord2f(1,1);
	//			glVertex2f(Size*0.49,-Size*0.09);
	//			glTexCoord2f(0,1);
	//			glVertex2f(-Size*0.49,-Size*0.09);				
	//		glEnd();
	//		
	//	glPopMatrix();
	//
	//glBindTexture(GL_TEXTURE_2D, ExpensiveTree.id);
	//glPushMatrix();
	//	glTranslatef(600,500,0);
	//	glBegin(GL_QUADS);
	//		glTexCoord2f(0,0);
	//		glVertex2f(-Size*0.49,Size*0.09);
	//		glTexCoord2f(1,0);
	//		glVertex2f(Size*0.49,Size*0.09);
	//		glTexCoord2f(1,1);
	//		glVertex2f(Size*0.49,-Size*0.09);
	//		glTexCoord2f(0,1);
	//		glVertex2f(-Size*0.49,-Size*0.09);				
	//	glEnd();
	//glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}


}


void Choices::DrawInGameText(std::string Text)
{
	glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);//needs to be called before RasterPos
    glRasterPos2i(0, 00);
    std::string s = Text;
    void * font = GLUT_BITMAP_9_BY_15;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        //this does nothing, color is fixed for Bitmaps when calling glRasterPos
        //glColor3f(1.0, 0.0, 1.0); 
        glutBitmapCharacter(font, c);
    }
    glColor3f(1,1,1);
    glPopMatrix();
}

void Choices::SetPopup(bool Pop)
{
	popup = Pop;
}