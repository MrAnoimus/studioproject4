#include "myapplication.h"
#include <mmsystem.h>

myApplication * myApplication::s_pInstance = NULL;

// you can use constructor to initialise variables
myApplication::myApplication()
: theCamera(NULL)
{
}

myApplication::~myApplication()
{
	if (theCamera != NULL)
	{
		delete theCamera;
		theCamera = NULL;
	}
}

myApplication* myApplication::getInstance()
{
	if(s_pInstance == NULL)
	{
		s_pInstance = new myApplication();
	}

	return s_pInstance;
}

void myApplication::Update(void) 
{
	//std::cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<std::endl;
	//std::cout<<(Menus.customButton[Menus.start].getPos()-customCursor.getPos()).GetMagnitude()<<std::endl;
	Menus.Update();
	if(customCursor.MouseOver(customCursor.getPos(),Menus.customButton[Menus.start].getPos()))
	{
		cnt1+=0.5f;
		Menus.customButton[Menus.start].setSelected(true);
	}else
	{
		Menus.customButton[Menus.start].setSelected(false);
	}
	if(mouseInfo.lastX < 800 || mouseInfo.lastX >0 || mouseInfo.lastY < 600 ||mouseInfo.lastY > 0 )
	{
		ShowCursor(false);
	}
	if(myKeys[27] == true)
	{
		exit(0);
	}
	if(myKeys['w'] == true)
	{

	}
	if(myKeys['a'] == true)
	{

	}
	if(myKeys['s'] == true)
	{

	}
	if(myKeys['d'] == true)
	{
	}
	if(myKeys[' '] == true)
	{
	}
}

void myApplication::renderScene(void)
{
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	theCamera->Update();

	if ((timeGetTime()-timelastcall)>1000/frequency)
	{
		// Calculate the framerate
		calculateFPS();

		timelastcall=timeGetTime();

		Update();
	}

	// Enable 2D text display and HUD
	theCamera->SetHUD( true );

		// Display them!
		RenderBackground();
		Menus.Draw();
		customCursor.Draw(mouseInfo.lastX,mouseInfo.lastY,customCursor.getPosZ(),customCursor.getSize());
		
		glPushMatrix();
			glColor3f(0,0,0);
			glRotatef(cnt1,0,0,1);
			glScalef(1,.8+.3*cos(cnt1/5),1);
			glTranslatef(-180,0,0);
			freetype::print(our_font, 320, 240, "Active FreeType Text\n - %7.2f", cnt1);
		glPopMatrix();
										
		// Display framerate
		drawFPS();

	theCamera->SetHUD( false );

	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}

void myApplication::changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void myApplication::inputKey(int key, int x, int y)
{

}

void myApplication::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;
}

void myApplication::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
}

void myApplication::MouseMove (int x, int y)
{
	mouseInfo.lastX = x;
	mouseInfo.lastY = y;
	customCursor.setPosX(mouseInfo.lastX-customCursor.getSize());
	customCursor.setPosY(mouseInfo.lastY-customCursor.getSize());
}

void myApplication::MouseClick(int button, int state, int x, int y)
{
	switch (button)
	{

		case GLUT_LEFT_BUTTON:
		{
			mouseInfo.mLButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;
			/*std::cout<<x<<","<<y<<std::endl;*/
			if (mouseInfo.mLButtonUp) 
			{
				//	Add codes to manage the bullets shot out and the remaining bullets
				/*if(customCursor.MouseOver(customButton.getPos()))
				{
					std::cout<<customCursor.MouseOver(customButton.getPos())<<std::endl;
				}*/
			}

		}break;

		case GLUT_RIGHT_BUTTON:
		{

		}break;

		case GLUT_MIDDLE_BUTTON:
		{

		}break;
	}
}

bool myApplication::Init(void)
{
	// Set camera position
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );

	// Enable Texture Mapping ( NEW )
	glEnable(GL_TEXTURE_2D);
	LoadTGA(&BackgroundTexture,"images/XPDefaultBackground.tga");
	our_font.init("FFF_Tusj.TTF", 42);
	cnt1 = 0;
	//  The number of frames
	frameCount = 0;
	//  Number of frames per second
	fps = 0;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	currentTime = 0, previousTime = 0;
	//  Pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	// realtime loop control
	timelastcall=timeGetTime();
	frequency = 30.0f;
	for(int i=0; i<255; i++)
	{
		myKeys[i] = false;
	}
	angle = 0.0f;
	mouseInfo.lastX = glutGet(GLUT_WINDOW_WIDTH) >> 1;
	mouseInfo.lastY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;
	return true;
}

/****************************************************************************************************
   Draw the background
 ****************************************************************************************************/
void myApplication::RenderBackground(void) 
{
	glEnable(GL_TEXTURE_2D);
	// Draw Background image
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture (GL_TEXTURE_2D, BackgroundTexture.texID);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
				glVertex2f(0,600);
				glTexCoord2f(1,0);
				glVertex2f(800,600);
				glTexCoord2f(1,1);
				glVertex2f(800,0);
				glTexCoord2f(0,1);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------
// Calculates the frames per second
//-------------------------------------------------------------------------
void myApplication::calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}
}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void myApplication::drawFPS()
{
	//  Load the identity matrix so that FPS string being drawn
	//  won't get animates
	glLoadIdentity ();

	//  Print the FPS to the window
	if (fps > 28.30f)
	{
		glColor3f( 1.0f, 1.0f, 1.0f);
	}
	else if (fps > 28.0f)
	{
		glColor3f( 0.0f, 1.0f, 0.0f);
	}else
	{
		glColor3f( 1.0f, 0.0f, 0.0f);
	}
	printw (25.0, 25.0, 0, "FPS: %4.2f", fps);
	glColor3f( 1.0f, 1.0f, 1.0f);
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void myApplication::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}