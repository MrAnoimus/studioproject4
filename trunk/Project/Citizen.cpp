#include "Citizen.h"



Citizen::Citizen(void)
	:TheMoods(Citizen::SAD)
	,TheFavourites(Citizen::SLACK)
	,TheBuildings(Citizen::NOTHING)
	,happy(false)
	,HappinessLevels(0)
	,active(true)
	,AnimationCounter(0.0f)
	,AnimationInvert(false)
	,RenderMood(false)
	,Name("JunHwee")
	,index(0)
	,Movedout(false)
	
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
}

Citizen::~Citizen(void)
{
}

void Citizen::MoodUpdate()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	static int ctime = glutGet(GLUT_ELAPSED_TIME);
	//std::cout <<"Citizen Position: " << GetPosition().x << std::endl;
	//if(dir==1)
	//{
	//	AnimationInvert=false;
	//	if(GetPosition().x+1<800)
	//	{
	//	//SetPosition(Vector3D(GetPosition().x+1,GetPosition().y,GetPosition().z));
	//	}
	//	else
	//	{
	//		dir=2;
	//	}
	//}
	//else if(dir==2)
	//{
	//	AnimationInvert=true;
	//	if(GetPosition().x-1>0)
	//	{
	//	//SetPosition(Vector3D(GetPosition().x-1,GetPosition().y,GetPosition().z));
	//	}
	//	else
	//	{
	//		dir=1;
	//	}
	//}
	if (time - ctime > 300) 
	{
		dir = rand() % 2 + 1;
		this->AnimationCounter--;
		if (this->AnimationCounter == 0)
		{
			this->AnimationCounter = 2;
		}
		ctime = time;
	}
	
	switch(TheFavourites)
	{
	case Citizen::FOOD:
		if(TheBuildings== Citizen::EATINGPLACE)
		{
			this->happy=true;
		}
		else
		{
			this->happy=false;
		}
		break;
	case Citizen::WORK:
		if(TheBuildings==Citizen::WORKPLACE)
		{
			this->happy=true;
		}
		else
		{
			this->happy=false;
		}
		break;
	case Citizen::SLACK:
		if(TheBuildings==Citizen::NOTHING)
		{
			this->happy=true;
		}
		else
		{
			this->happy=false;
		}
		break;
	default:
		std::cout << "Default" << std::endl;
		break;
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
		return "ENRAGE";
		break;
	case OKAY:
		return "OKAY";
		break;
	default:
		return "DEFAULT";
		break;
	}
}

std::string Citizen::GetPlace(void)
{
	switch(TheBuildings)
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
	default:
		return "DEFAULT";
		break;
	}
}

void Citizen::Draw()
{
	glEnable(GL_TEXTURE_2D);
	if(RenderMood==true)
	{
		glPushMatrix();
			glTranslatef(GetPosition().x-220,GetPosition().y,-2);
			StatsBoard();
		glPopMatrix();
	}
	glPushMatrix();
		glTranslatef(GetPosition().x,GetPosition().y,-2);
		RenderCitizen();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Citizen::SetFavourite(Favourite MyFavourite)
{
	this->TheFavourites = MyFavourite;
}

void Citizen::SetPlace(NearByBuilding myBuilding)
{
	this->TheBuildings = myBuilding;
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
		glVertex2f(70, 0);
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

void Citizen::StatsBoard(void)
{
	glPushMatrix();
		glTranslatef(85,50,0);
		DrawInGameText("Current Mood:");
	glPopMatrix();

	glColor3f(1,1,1);

		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, StatsBG.id);
			DrawSquare(180,100);
		glPopMatrix();
	

		glPushMatrix();
		glTranslatef(-70,50,-1);

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
		DrawSquare(20,20);
		glPushMatrix();
		glTranslatef(6,-40,-1);
		//DrawInGameText(GetMood());
		glPopMatrix();
	
	glPopMatrix();
	

	glPushMatrix();
	glTranslatef(0,-5,-1);
	glPushMatrix();
	glTranslatef(90,0,0);
	DrawInGameText("Favourite:");
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-30,0,0);
	DrawInGameText(GetFavourites());
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,-55,-1);
	glPushMatrix();
	glTranslatef(90,0,0);
	DrawInGameText("Current Place:");
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-70,0,0);
	DrawInGameText(GetPlace());
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