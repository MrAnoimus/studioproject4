#include "Citizen.h"

Citizen::Citizen(void)

	:TheMoods(Citizen::SAD)
	,TheFavourites(Citizen::SLACK)
	,happy(false)
	,HappinessLevels(0)
	,active(false)
	,AnimationCounter(0.0f)
	,AnimationInvert(false)
	,RenderMood(false)
	,Name("JunHwee")
	,index(0)
	,Movedout(false)
	,MovedBack(false)
	,owner("JunHwee")
	,sheltered(false)

{
	glEnable(GL_TEXTURE_2D);
	LoadTGA(&Okay, "Textures/Smiley.tga");
	LoadTGA(&Happy, "Textures/Happy.tga");
	LoadTGA(&Enraged, "Textures/Enraged.tga");
	LoadTGA(&Sad, "Textures/Sad.tga");
	LoadTGA(&FemaleCitizen, "Textures/FemaleCitizen.tga");
	LoadTGA(&MaleCitizen, "Textures/MaleCitizen.tga");
	LoadTGA(&StatsBG, "Textures/MoodBackground.tga");

	CitizenDestination = new Destination();

	srand(time(NULL));

	int Random = rand() % 3 + 1;	
	if(Random==1)
	{
		SetFavourite(Citizen::FOOD);
	}
	else if(Random==2)
	{
		SetFavourite(Citizen::SLACK);
	}
	else if(Random==3)
	{
		SetFavourite(Citizen::WORK);
	}
	srand(time(NULL));

	int Random2 = rand() % 2 + 1;	
	if(Random2==1)
	{
		Gender=1;
	}
	else
	{
		Gender=2;
	}
	for(int i = 0; i<3; i++)
	{
		TheBuildings[i] = Citizen::WORKPLACE;
	}
}

Citizen::~Citizen(void)
{
}

void Citizen::MoodUpdate()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	static int ctime = glutGet(GLUT_ELAPSED_TIME);
	if (time - ctime > 100) 
	{
		dir = rand() % 2 + 1;
		this->AnimationCounter--;
		if (this->AnimationCounter == 0)
		{
			this->AnimationCounter = 2;
		}
		ctime = time;
	}
	for(int i=0; i <4; i++)
	{

		if(TheFavourites == Citizen::FOOD)
		{
			if(TheBuildings[i]==Citizen::EATINGPLACE)
			{
				this->happy=true;
				break;
			}
			else
			{
				this->happy=false;
			}

		}
		if(TheFavourites == Citizen::WORK)
		{
			if(TheBuildings[i]==Citizen::WORKPLACE)
			{
				this->happy=true;
				break;
			}else
			{
				this->happy=false;
			}
		}
		if(TheFavourites == Citizen::SLACK)
		{
			if(TheBuildings[i]==Citizen::NOTHING)
			{
				this->happy=true;
				break;
			}else
			{
				this->happy=false;
			}
		}
		
	}
	if(this->happy==true)
	{
		if(this->HappinessLevels<=99)
		{
			this->HappinessLevels++;
		}
	}
	else if(this->happy==false)
	{
		if(this->HappinessLevels>=1)
		{
			this->HappinessLevels--;
		}
	}

	if(this->HappinessLevels>0)
	{
		this->TheMoods=Citizen::ENRAGE;

	}
	if(this->HappinessLevels>25)
	{
		this->TheMoods=Citizen::SAD;
	}
	if(this->HappinessLevels>50)
	{
		this->TheMoods= Citizen::OKAY;
	}
	if(this->HappinessLevels>75)
	{
		this->TheMoods=Citizen::HAPPY;

	}
	/*std::cout <<"Happiness Level: " << HappinessLevels << std::endl;
	std::cout <<"TheMood: " << GetMood() << std::endl;
	std::cout <<"TheFavourite: " << GetFavourites() << std::endl;
	std::cout <<"ThePlace: " << GetPlace() << std::endl;*/

}

std::string Citizen::GetFavourites(void)
{
	switch(TheFavourites)
	{
	case FOOD:
		return "FOOD";
		break;
	case WORK:
		return "WORK";
		break;
	case SLACK:
		return "SLACK";
		break;
	default:
		return "DEFAULT";
		break;
	}
}

std::string Citizen::GetMood(void)
{
	switch(TheMoods)
	{
	case HAPPY:
		return "HAPPY";
		break;
	case SAD:
		return "SAD";
		break;
	case ENRAGE:
		return "ENRAGED";
		break;
	case OKAY:
		return "OKAY";
		break;
	default:
		return "DEFAULT";
		break;
	}
}

std::string Citizen::GetPlace(int i)
{
	
	switch(TheBuildings[i])
	{
	case EATINGPLACE:
		return "EATINGPLACE";
		break;
	case WORKPLACE:
		return "WORKPLACE";
		break;
	case NOTHING:
		return "NOTHING";
		break;
	case HOUSES:
		return "HOUSES";
		break;
	default:
		return "DEFAULT";
		break;
	
	}
}

void Citizen::Draw(float PositionX, float PositionY)
{
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glPushMatrix();
	glTranslatef(this->GetPosition().x,this->GetPosition().y,-2);
	RenderCitizen();

	
	glPopMatrix();
	
	
	if(this->RenderMood==true)
	{
		glPushMatrix();
		glTranslatef(PositionX-200,PositionY,-2);
		this->StatsBoard();
		glPopMatrix();
	}
	
	glDisable(GL_TEXTURE_2D);
}

void Citizen::SetFavourite(Favourite MyFavourite)
{
	this->TheFavourites = MyFavourite;
}

void Citizen::SetPlace(std::string tag, int i)
{
	NearByBuilding myBuilding=Citizen::NOTHING;
	if(tag == "workplace")
	{
		myBuilding = Citizen::WORKPLACE;
	}
	if(tag == "eatingplace")
	{
		myBuilding = Citizen::EATINGPLACE;
	}
	if(tag =="nothing")
	{
		myBuilding = Citizen::NOTHING;
	}
	if(tag =="house")
	{
		myBuilding = Citizen::HOUSES;
	}
	this->TheBuildings[i] = myBuilding;
}

void Citizen::RenderCitizen(void)
{
	glPushMatrix();
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(Gender==1)
	{
		glBindTexture(GL_TEXTURE_2D, FemaleCitizen.id);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, MaleCitizen.id);
	}
	glBegin(GL_QUADS);
	if(AnimationInvert==false)
	{
		glTexCoord2f(0.25 * AnimationCounter, 1); 
		glVertex2f(50, 70);
		glTexCoord2f(0.25 * AnimationCounter, 0); 
		glVertex2f(50, 0);
		glTexCoord2f(0.25 * AnimationCounter + 0.25, 0);
		glVertex2f(0, 0);
		glTexCoord2f(0.25 * AnimationCounter + 0.25, 1);
		glVertex2f(0, 70);
	}
	else if(AnimationInvert==true)
	{
		glTexCoord2f(0.25 * AnimationCounter + 0.25, 1);
		glVertex2f(50, 70);
		glTexCoord2f(0.25 * AnimationCounter + 0.25, 0);
		glVertex2f(50, 0);
		glTexCoord2f(0.25 * AnimationCounter, 0);
		glVertex2f(0,0);
		glTexCoord2f(0.25 * AnimationCounter, 1); 
		glVertex2f(0, 70);

	}
	glEnd();
	glPopMatrix();
}

void Citizen::DrawSquare(float xSize, float ySize)
{
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex2f(xSize,-ySize);
	glTexCoord2f(1,1);
	glVertex2f(xSize,ySize);
	glTexCoord2f(0,1);
	glVertex2f(-xSize,ySize);
	glTexCoord2f(0,0);
	glVertex2f(-xSize,-ySize);
	glEnd();
}

void Citizen::SetAnimationCounter(int AnimationCounter)
{
	this->AnimationCounter=AnimationCounter;
}

int Citizen::GetAnimationCounter(void)
{
	return this->AnimationCounter;
}

void Citizen::StatsBoard()
{
	
	
	int TranslateZ=-1;
	glColor3f(1,1,1);
	glEnable(GL_BLEND);//blend 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//
	glEnable(GL_TEXTURE_2D);//texture 1
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, StatsBG.id);
		DrawSquare(160,100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);//end of texture 1
	//

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);//texture 2
		glTranslatef(-40,30,-1);

		if(this->GetMood()=="HAPPY")
		{
			glBindTexture(GL_TEXTURE_2D,Happy.id);
		}
		else if(this->GetMood()=="ENRAGED")
		{
			glBindTexture(GL_TEXTURE_2D, Enraged.id);
		}
		else if(this->GetMood()=="SAD")
		{
			glBindTexture(GL_TEXTURE_2D, Sad.id);
		}
		else if(this->GetMood()=="OKAY")
		{
			glBindTexture(GL_TEXTURE_2D, Okay.id);
		}
		
		DrawSquare(10,10);
		glDisable(GL_TEXTURE_2D);//end of texture 2
		
	glPopMatrix();
	glDisable(GL_BLEND);//end of blend 1

	glPushMatrix();
		glPushMatrix();
			glTranslatef(90,30,0);
			DrawInGameText("Current Mood:");
		glPopMatrix();
		glTranslatef(0,-5,TranslateZ);
		glPushMatrix();
			glTranslatef(90,60,0);
			DrawInGameText("Name/Owner:");
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-30,80,TranslateZ);
			DrawInGameText(owner);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(90,0,TranslateZ);
			DrawInGameText("Favourite:");
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-30,0,TranslateZ);
			DrawInGameText(GetFavourites());
		glPopMatrix();

		glTranslatef(0,-25,TranslateZ);
		glPushMatrix();
			glTranslatef(90,0,0);
			DrawInGameText("NearbyPlace:");
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-30,0,TranslateZ);
			int translateY = 0;
			for(int i =0; i<4; i++)
			{
				glTranslatef(0, translateY ,0);
				translateY -=10;
				translateY = -10;
				DrawInGameText(GetPlace(i));
		
			}
	
		glPopMatrix();
	glPopMatrix();

	
}

void Citizen::DrawInGameText(std::string Text)
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

	glPopMatrix();
}

void Citizen::SetName(std::string InputName)
{
	this->Name= InputName;
}

std::string Citizen::GetName(void)
{
	return this->Name;
}