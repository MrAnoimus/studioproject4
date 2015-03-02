#include "MiniGame.h"

MiniGame::MiniGame(void)
{	

}

MiniGame::~MiniGame(void)
{
	theCamera = NULL;
}

bool MiniGame::Init(Camera* theCamera)
{
	cash = 0;

	//for mini game
	minigame = false;
	addcash = false;
	playing = false;
	gravity.Set(0, -9.8f, 0);
	fallspeed = 1;
	CposX = Math::RandIntMinMax(320, 780);
	CposY = 110;
	spawntime = 0;

	//animation
	mgctr = mgctr2 = mgctr3 = 0;
	spritectime = 0, spriteptime = 0, tctime = 0, tptime = 0, timer = 10;
	inverted = true;

	//Sound Engine init
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine)
	{
		return false;
	}
	mgsfx = NULL;
	chaching = NULL;

	this->theCamera = theCamera;

	//mini game coin init
	for (int i = 0; i <MAX_COIN; ++i)
	{
		GameObject *mg = new GameObject(GameObject::GO_COIN);
		//mg->active = true;
		mg->vel.y = -200;
		/*mg->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;*/
		 mg->pos.x = Math::RandIntMinMax(20, 450);
		mg->pos.y = Math::RandIntMinMax(350, 450);
		m_goList.push_back(mg);
	}

	//mini game catcher init
	catcher = new GameObject(GameObject::GO_CATCHER);
	catcher->active = true; 
	catcher->pos.x = 400;
	catcher->pos.y = 50;

	return true;
}

void MiniGame::Update()
{
	//START FOR ALL OF MINI GAME==================================================
	//for mini game animation
	static int frame = 0;
	static int lastTime = glutGet(GLUT_ELAPSED_TIME);
	++frame;
	int time = glutGet(GLUT_ELAPSED_TIME);
	float dt = (time - lastTime) / 1000.f;

	lastTime = time;

	spawntime -= dt*0.001;

	tctime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval2 = tctime - tptime;


		if(timeInterval2 > 1000)
		{
			tptime = tctime;
				timer--;

			if(timer <= 0 )
			{
				timer = 0;
			}

			if(timer <= 0 && playing == true )
			{
				playing = false;
				addcash = true;
			}
		}

		if(addcash)
		{
			if(chaching == NULL)
			{chaching = theSoundEngine->play2D ("SFX/chaching.wav", false, true);}		
			else
			{chaching == NULL;
			 chaching = theSoundEngine->play2D ("SFX/chaching.wav", false, true);}
			if(chaching->getIsPaused() == true)
			{chaching->setIsPaused(false);}
			else if(chaching->isFinished() == true)
			{chaching = NULL;}
		}

	spritectime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = spritectime - spriteptime;
	if(timeInterval > 150)
	{
		spriteptime = spritectime;
		mgctr++;
		mgctr3++;
	}

	if(mgctr == 7){mgctr = 0;}
	if(mgctr3 == 11){mgctr = 0;}

	/*if(timer <= 0)
	{
		playing = false;
	}*/

	if(!m_goList.empty())
	{
		for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *mg = (GameObject *)*it;
			if(mg->active)
			{
				if(mg->type == GameObject::GO_COIN)
				{//coin falling update
					/*mg->vel +=  minigameobjects->gravity * dt;*/
					mg->vel.y = -200;
					if(mg->vel.y <= -200)
					{mg->vel.y = -200;}
					mg->pos += fallspeed * (mg->vel + (mg->vel + gravity * dt)) * 0.5 * dt;

					/*if(mg->pos.y <= (600 - 200 + theCamera->GetPosition().y - 350))*/
					if(mg->pos.y <= catcher->pos.y)
					{
						mg->vel.y = -200;
						/*mg->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;*/
						mg->pos.x = Math::RandIntMinMax(20, 450);
						mg->pos.y = Math::RandIntMinMax(350, 450);
					/*	mg->pos.x = 400;
						mg->pos.y = 490;*/
					}
				

					if(catcher->active)
					{
						if(catcher->type == GameObject::GO_CATCHER)
						{
							if((catcher->pos-mg->pos).Length()<=60)
							{
								mg->counter--;
								it = m_goList.erase(it);
								
								cash += 10;
								//resource->SetMoney(resource->GetMoney()+100);

								if(mgsfx == NULL)
								{
									mgsfx = theSoundEngine->play2D ("SFX/coin.wav", false, true);
								}else
								{
									mgsfx == NULL;
									mgsfx = theSoundEngine->play2D ("SFX/coin.wav", false, true);
								}
								if(mgsfx->getIsPaused() == true)
								{
									mgsfx->setIsPaused(false);
								}
								else if(mgsfx->isFinished() == true)
								{
									mgsfx = NULL;
								}
								break;
							}
							if(catcher->pos.x <= 20){catcher->pos.x = 20;}
							if(catcher->pos.x >= 430){catcher->pos.x = 430;}
						}

					}
				}
			}
			else if((spawntime <= 0) && (mg->counter < MAX_COIN))
			{
				spawntime = SPAWN_TIME;
				GameObject *mg2 = new GameObject(GameObject::GO_COIN);
				mg2->active = true;
				mg2->vel.y = -200;
				if(mg2->vel.y <= -200)
				{mg2->vel.y = -200;}
				mg2->counter++;
				/*mg2->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;*/
				mg2->pos.x = Math::RandIntMinMax(20, 450);
				mg2->pos.y = Math::RandIntMinMax(350, 450);

			
				for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					GameObject *mg3 = (GameObject *)*it;
					if(mg3->active)
					{
						if(mg3->type == GameObject::GO_COIN)
						{
							if((mg2->pos - mg->pos).Length() <= 60)
							{
								Math::RandIntMinMax(20, 450);
							}
						}
					}
				}
				m_goList.push_back(mg2);

				break;
			}
		}
	}
			if(timer <= 0)
			{
				if(!m_goList.empty())
				m_goList.clear();
			}
		//END FOR ALL OF MINI GAME==================================================
}

void MiniGame::Draw()
{

	glPushMatrix();//3
	glTranslatef(150,50,0);
	glBindTexture (GL_TEXTURE_2D, MGTexture[0].id);
	DrawMGBG();
	
	glPushMatrix();
		glTranslatef(280,420,-5);
		DrawHourGlass(MGTexture[3].id);
	glPopMatrix();

	glTranslatef(0,0,-5);
	//rendering of coins
	if(!m_goList.empty())
	{
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *mg = (GameObject *)*it;
			if (mg->active)
			{
				DrawObject(mg, MGTexture[1].id);
			}
		}
	}
	//rendering of catcher
	GameObject *catcher2 = (GameObject *)catcher;
	if (catcher2->active)
	{
		DrawObject(catcher2, MGTexture[2].id);
	}

	glPopMatrix();//3
}

void MiniGame::DrawMGBG()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(1,1);
				glVertex2f(0,500);
				glTexCoord2f(0,1);
				glVertex2f(500,500);
				glTexCoord2f(0,0);
				glVertex2f(500,0);
				glTexCoord2f(1,0);
				glVertex2f(0,0);				
			glEnd();
		glPopMatrix();
		glColor3f(1,1,1);
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void MiniGame::DrawTextureBase()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.125 * mgctr , 1);glVertex2f(30, 30);
		glTexCoord2f(0.125 * mgctr , 0);glVertex2f(30, 0);
		glTexCoord2f(0.125 * mgctr + 0.125, 0);glVertex2f(0, 0);
		glTexCoord2f(0.125 * mgctr + 0.125, 1);glVertex2f(0, 30);
	glEnd();

}

void MiniGame::DrawTextureBaseNotInvert()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 1);glVertex2f(60, 60);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 0);glVertex2f(60, 0);
		glTexCoord2f(0.125 * mgctr2, 0);glVertex2f(0,0);
		glTexCoord2f(0.125 * mgctr2, 1);glVertex2f(0, 60);
	glEnd();
}

void MiniGame::DrawTextureBaseInvert()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.125 * mgctr2 , 1);glVertex2f(60, 60);
		glTexCoord2f(0.125 * mgctr2 , 0);glVertex2f(60, 0);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 0);glVertex2f(0, 0);
		glTexCoord2f(0.125 * mgctr2 + 0.125, 1);glVertex2f(0, 60);
	glEnd();
}

void MiniGame::DrawTextureBaseHG()
{
	glBegin(GL_QUADS);
		glTexCoord2f(0.0909090909090909 * mgctr3 , 1);glVertex2f(50, 50);
		glTexCoord2f(0.0909090909090909 * mgctr3 , 0);glVertex2f(50, 0);
		glTexCoord2f(0.0909090909090909 * mgctr3 + 0.0909090909090909, 0);glVertex2f(0, 0);
		glTexCoord2f(0.0909090909090909 * mgctr3 + 0.0909090909090909, 1);glVertex2f(0, 50);
	glEnd();
}

void MiniGame::DrawObject(GameObject *mg, const GLuint Texture)
{
	switch(mg->type)
	{
	case GameObject::GO_COIN:
		{
			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, Texture);
			glPushMatrix();
			glTranslatef(mg->pos.x, mg->pos.y, mg->pos.z);
			glScalef(mg->scale.x, mg->scale.y, mg->scale.z);
			DrawTextureBase();
			glPopMatrix();
			glDisable(GL_BLEND);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}
		break;
	case GameObject::GO_CATCHER:
		{
			glColor3f(1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glEnable(GL_BLEND); 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture (GL_TEXTURE_2D, Texture);
			glPushMatrix();
			glTranslatef(mg->pos.x, mg->pos.y, mg->pos.z);
			glScalef(mg->scale.x, mg->scale.y, mg->scale.z);

			if(!inverted)
			{
				DrawTextureBaseNotInvert();
			}
			else
			{
				DrawTextureBaseInvert();
			}

			glPopMatrix();
			glDisable(GL_BLEND);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);

		}
		break;
	}
}

void MiniGame::DrawHourGlass(const GLuint Texture)
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture (GL_TEXTURE_2D, Texture);
			glPushMatrix();
				DrawTextureBaseHG();
			glPopMatrix();
		glDisable(GL_BLEND);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void MiniGame::CoinPattern1(float posX, float posY, float width)
{
	/*for(int i = 0; i < glutGet(GLUT_SCREEN_WIDTH)/32; i+=32)
	{
		if(mg->type = GameObject::GO_COIN)
		{
			if(i%2 == 0)
			{

			}
		}
	
	}*/

}
//glutGet(GLUT_SCREEN_WIDTH);
//glutGet(GLUT_SCREEN_HEIGHT);