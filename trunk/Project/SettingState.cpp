#include "SettingState.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "introstate.h"
#include <mmsystem.h>
#include <iostream>
#include <fstream>
using namespace std;

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}


CSettingState CSettingState::theSettingState;


void CSettingState::changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
	{
		h = 1;
	}
	float ratio = (float) (1.0f* w / h);
	sizechanged = true;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,10000);
	glMatrixMode(GL_MODELVIEW);
}
void CSettingState::KeyboardDown(unsigned char key, int x, int y)
{
	myKeys[key]= true;
	cout<<"Key: "<<key<<" STATE : " <<myKeys[key]<<endl;
}

void CSettingState::KeyboardUp(unsigned char key, int x, int y)
{
	myKeys[key]= false;
	cout<<"Key: "<<key<<" STATE : " <<myKeys[key]<<endl;
}
void CSettingState::MouseMove(int x , int y)
{
	int diffX = x - mouseInfo.lastX;
	int diffY = y - mouseInfo.lastY;

		//check if mouse pointer is inside the button boundaries
	for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
	{
		(*it)->UpdateMouseMove(x,y);
	}

	//Update on y axis
	theCamera->Pitch( diffY * 3.142f / 180.0f );

	////Update on x and z axis
	angle += (float) diffX * 3.142f / 180.0f;
	if (angle > 6.284f)
		angle -= 6.284f;
	else if (angle < -6.284f)
		angle += 6.284f;
	theCamera->Yaw( -angle );

	mouseInfo.lastX = x;
	mouseInfo.lastY = y;

}
void CSettingState::MouseClick(int button , int state , int x , int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		{
			mouseInfo.mLButtonUp = state;
			mouseInfo.lastX = x;
			mouseInfo.lastY = y;
			//cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<endl;

			if (!mouseInfo.mLButtonUp)
			{
				for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
				{
					if ((*it)->buttonhover)
						(*it)->buttonclicked = true;
				}
			}

			else
			{
				for (vector<ButtonClass*>::iterator it = ListofButtons.begin(); it != ListofButtons.end(); ++it)
				{
					if ((*it)->buttonhover)
						(*it)->buttonclicked = false;
				}
			}

			/*if (mouseInfo.lastX >=290 && mouseInfo.lastX <= 350 && mouseInfo.lastY >= 150 && mouseInfo.lastY <=200)
			{
				if (volume <= 0.8)
				{
					volume += 0.10;
					cout << volume << "\n";
					mouseInfo.mLButtonUp = false;
				}

			}

			if (mouseInfo.lastX >=665 && mouseInfo.lastX <= 735 && mouseInfo.lastY >= 160 && mouseInfo.lastY <=185)
			{
				if  ( volume > 0.2)
				{		
					volume -= 0.10f;
					cout << volume << "\n";
					mouseInfo.mLButtonUp = false;		
				}
			}*/

		}break;
		case GLUT_RIGHT_BUTTON:
		{
			cout << volume;
		}break;
		case GLUT_MIDDLE_BUTTON:
		{

		}break;
	}
}
bool CSettingState::Init()
{

	//Read a value from the lua text file
	lua_State *L2 = lua_open();
	luaL_openlibs(L2);
	if (luaL_loadfile(L2, "LuaScript/test.lua") || lua_pcall(L2, 0, 0, 0))
	{
		printf("error: %s", lua_tostring(L2, -1));
		return -1;
	}
	lua_getglobal(L2,"VOLUME");
	double VOLUME = lua_tonumber(L2, 1);

	volume =  VOLUME;
	lua_close(L2);
	theCamera = new Camera( Camera::LAND_CAM );
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );


	LoadTGA(&BackgroundTexture,"Textures/obg.tga");
	LoadTGA(&Icons[0],"Textures/plus.tga");
	LoadTGA(&Icons[1],"Textures/minus.tga");
	LoadTGA(&Icons[2],"Textures/bar.tga");

	our_font.init("Fonts/FFF_Tusj.TTF", 42);

	//  The number of frames
	frameCount = 0;
	//  Number of frames per second
	fps = 0;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	currentTime = 0, previousTime = 0;

	// realtime loop control
	timelastcall=timeGetTime();
	frequency = 30.0f;
	for(int i=0; i<255; i++)
	{
		myKeys[i] = false;
		//cout<<i<<":"<<myKeys[i]<<endl;
	}
	angle = 0.0f;

	mouseInfo.lastX = 800 >> 1;
	mouseInfo.lastY = 600 >> 1;
	//mouseInfo.lastX = glutGet(GLUT_WINDOW_WIDTH) >> 1;
	//mouseInfo.lastY = glutGet(GLUT_WINDOW_HEIGHT) >> 1;

	SaveButton = new ButtonClass();
	LoadTGA(&SaveButton->button[0],"Textures/confirmup.tga");
	LoadTGA(&SaveButton->button[1],"Textures/confirmdown.tga");
	SaveButton->Set(100,300,460,500);
	ListofButtons.push_back(SaveButton);

	ExitButton = new ButtonClass();
	LoadTGA(&ExitButton->button[0],"Textures/cancelup.tga");
	LoadTGA(&ExitButton->button[1],"Textures/canceldown.tga");
	ExitButton->Set(500,700,460,500);
	ListofButtons.push_back(ExitButton);

	PlusButton = new ButtonClass();
	LoadTGA(&PlusButton->button[0],"Textures/plusup.tga");
	LoadTGA(&PlusButton->button[1],"Textures/plusdown.tga");
	PlusButton->Set(650,700,160,200);
	ListofButtons.push_back(PlusButton);

	MinusButton = new ButtonClass();
	LoadTGA(&MinusButton->button[0],"Textures/minusup.tga");
	LoadTGA(&MinusButton->button[1],"Textures/minusdown.tga");
	MinusButton->Set(300,350,170,190);
	ListofButtons.push_back(MinusButton);
	return true;
}
void CSettingState::Cleanup()
{
	//cout << "CSettingState::Cleanup\n" << endl;
}

void CSettingState::Pause()
{
	//cout << "CSettingState::Pause\n" << endl;
}

void CSettingState::Resume()
{
	//cout << "CSettingState::Resume\n" << endl;
}

void CSettingState::HandleEvents(CGameStateManager* theGSM)
{
	if (mouseInfo.mLButtonUp) 
	{		
		mouseInfo.mLButtonUp = false;	
	}
	if(myKeys[27]==true)
	{
		exit(0);
	}
	if(myKeys['w'] == true)
	{
		theGSM->ChangeState( CPlayState::Instance() );
	}
}

void CSettingState::Update(CGameStateManager* theGSM)
{
	//cout << "CSettingState::Update\n" << endl;
	//MouseMove(mouseInfo.lastX,mouseInfo.lastY);
	//std::cout<<mouseInfo.lastX<<","<<mouseInfo.lastY<<std::endl;
	if (sizechanged)
		{
			SaveButton->Set(300,520,460,520);
			ExitButton->Set(350,450,520,580);
			PlusButton->Set(100,150,100,140);
			MinusButton->Set(500,550,100,140);
			sizechanged = false;
		}

		if(SaveButton->buttonclicked)
		{
		
			ofstream file;
			file.open("LuaScript/test.lua");
			file <<"VOLUME = ";
			file << volume;
			file.close();
			theGSM->ChangeState( CIntroState::Instance() );
			mouseInfo.mLButtonUp = false;
			SaveButton->buttonclicked = false;
		}

		if(PlusButton->buttonclicked)
		{
			if (volume <= 0.8)
			{
				volume += 0.20;
				mouseInfo.mLButtonUp = false;
				PlusButton->buttonclicked = false;
			}
		}

		if(MinusButton->buttonclicked)
		{
			if  ( volume > 0.2)
			{
				volume -= 0.20;
				mouseInfo.mLButtonUp = false;
				MinusButton->buttonclicked = false;
			}
		}

		if(ExitButton->buttonclicked)
		{
			theGSM->ChangeState( CIntroState::Instance() );
			mouseInfo.mLButtonUp = false;
			ExitButton->buttonclicked = false;
		}

	
}

void CSettingState::Draw(CGameStateManager* theGSM) 
{
	//cout << "CSettingState::Draw\n" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	theCamera->Update();
	/*this->HandleEvents(theGSM);*/
	if ((timeGetTime()-timelastcall)>1000/frequency)
	{
		// Calculate the framerate
		calculateFPS();
		timelastcall=timeGetTime();
	}
	// Enable 2D text display and HUD
	theCamera->SetHUD( true );

	
	glEnable(GL_TEXTURE_2D);

	// Draw Background image
	glPushMatrix();
		//glScalef(0.1,0.1,0.1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture (GL_TEXTURE_2D, BackgroundTexture.id);
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
		//glDisable(GL_BLEND);
	glPopMatrix();

	drawvolumebars();

	glPushMatrix();
		SaveButton->Render();
		ExitButton->Render();
		PlusButton->Render();
		MinusButton->Render();
	glPopMatrix();



	glDisable(GL_TEXTURE_2D);
	//drawFPS();
	theCamera->SetHUD( false );
	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	glutPostRedisplay();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
void CSettingState::calculateFPS()
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
void CSettingState::drawFPS()
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
	print(our_font, 0, 550,"FPS: %4.2f", fps);
	glColor3f( 1.0f, 1.0f, 1.0f);
}
bool CSettingState::LoadTGA(TextureImage *texture, char *filename)			// Loads A TGA File Into Memory
{    
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	GLubyte		TGAcompare[12];								// Used To Compare TGA Header
	GLubyte		header[6];									// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;										// Temporary Variable
	GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

	FILE *file = fopen(filename, "rb");						// Open The TGA File

	if(	file==NULL ||										// Does File Even Exist?
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
		fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
	{
		if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
			return false;									// Return False
		else
		{
			fclose(file);									// If Anything Failed, Close The File
			return false;									// Return False
		}
	}

	texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)
    
 	if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
		texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
		(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
	{
		fclose(file);										// If Anything Failed, Close The File
		return false;										// Return False
	}

	texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
	bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
	imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

	texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

	if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
	{
		if(texture->imageData!=NULL)						// Was Image Data Loaded
			free(texture->imageData);						// If So, Release The Image Data

		fclose(file);										// Close The File
		return false;										// Return False
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
	{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
		temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
		texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
		texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
	}

	fclose (file);											// Close The File

	// Build A Texture From The Data
	glGenTextures(1, &texture[0].id);					// Generate OpenGL texture IDs

	glBindTexture(GL_TEXTURE_2D, texture[0].id);			// Bind Our Texture
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered
	
	if (texture[0].bpp==24)									// Was The TGA 24 Bits
	{
		type=GL_RGB;										// If So Set The 'type' To GL_RGB
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											// Texture Building Went Ok, Return True
}

void CSettingState::draw()
{
	glPushMatrix();
	glTranslatef(0,0,-1);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex2f(-50,50);
		glTexCoord2f(1,0);
		glVertex2f(50,50);
		glTexCoord2f(1,1);
		glVertex2f(50,-50);
		glTexCoord2f(0,1);
		glVertex2f(-50,-50);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CSettingState::drawvolumebars()
{
	//bar
	if ( volume <= 1 && volume > 0.8f  )
	{
		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(400,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(450,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(500,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(550,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(600,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();
	}

	else if  ( volume <= 0.8f && volume >0.6f)
	{
		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(400,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(450,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(500,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(550,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();
	}

	else if (volume <= 0.6f && volume >0.4f)
	{
		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(400,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(450,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(500,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();
	}

	else if ( volume <= 0.4f && volume >0.2f)
	{
		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(400,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(450,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();

	}

	else if ( volume <= 0.2f && volume > 0)
	{
		glPushMatrix();
			glBindTexture (GL_TEXTURE_2D, Icons[2].id);
			glTranslatef(400,175,0);
			glScalef(0.5,0.65,0);
			draw();
		glPopMatrix();
	}

	else 
	{
		
	}
}