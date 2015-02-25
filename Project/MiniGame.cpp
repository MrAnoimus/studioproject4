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
	cout << "initialising" << endl;
	//mini game coins
		
	cout << "init" << endl;
	//for mini game
	minigame = false;
	gravity.Set(0, -9.8f, 0);
	fallspeed = 1;
	CposX = Math::RandIntMinMax(320, 780);
	CposY = 110;
	spawntime = 0;

	//animation
	mgctr = 0, mgctr2 = 0;
	inverted = true;

	//Sound Engine init
	theSoundEngine = createIrrKlangDevice();
	if (!theSoundEngine)
	{
		return false;
	}
	this->theCamera = theCamera;
	for (int i = 0; i <MAX_COIN; ++i)
	{
		GameObject *mg = new GameObject(GameObject::GO_COIN);
		//mg->active = true;
		mg->vel.y = -200;
		mg->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
		mg->pos.y = 600 - Math::RandIntMinMax(110, 310) + theCamera->GetPosition().y - 300;
		m_goList.push_back(mg);
	}

	//mini game catcher
	catcher = new GameObject(GameObject::GO_CATCHER);
	catcher->active = true; 
	catcher->pos.x = 400;
	catcher->pos.y = 50;

	spritectime = 0, spriteptime = 0, tctime = 0, tptime = 0, timer = 300;
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
			if(timer <= 0)
			{
				timer = 0;
			}
		}


	spritectime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = spritectime - spriteptime;
	if(timeInterval > 150)
	{
		spriteptime = spritectime;
		mgctr++;
	}

	if (mgctr == 7)
	{
		mgctr = 0;
	}

		for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *mg = (GameObject *)*it;
			if(mg->active)
			{
				cout << mg->counter << endl;
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
						mg->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
						mg->pos.y = 600 - Math::RandIntMinMax(110, 310) + theCamera->GetPosition().y - 300;
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
								resource->SetMoney(resource->GetMoney()+100);

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
							if(catcher->pos.x <= 150){catcher->pos.x = 150;}
							if(catcher->pos.x >= 590){catcher->pos.x = 590;}
						}

					}
				}
			}
			else if((spawntime <= 0) && (mg->counter < MAX_COIN) && timer > 0)
			{
				spawntime = SPAWN_TIME;
				GameObject *mg2 = new GameObject(GameObject::GO_COIN);
				mg2->active = true;
				mg2->vel.y = -200;
				if(mg2->vel.y <= -200)
				{mg2->vel.y = -200;}
				mg2->counter++;
				mg2->pos.x = 800 - Math::RandIntMinMax(320, 780) + theCamera->GetPosition().x - 400;
				mg2->pos.y = 600 - Math::RandIntMinMax(110, 150) + theCamera->GetPosition().y - 300;
				m_goList.push_back(mg2);

				break;
			}
		}
		//END FOR ALL OF MINI GAME==================================================
}

void MiniGame::Draw()
{
	//for mini game
	/*if(minigame)
	{*/
		//DRAW THIS STUFF IN THE MINIGAME CLASS PLEASE
		glPushMatrix();
		glTranslatef(150,50,-1);
		glBindTexture (GL_TEXTURE_2D, MGBackgroundTexture.id);
		DrawMGBG();

		//rendering of coins
		for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			GameObject *mg = (GameObject *)*it;
			if (mg->active)
			{
				cout << "draw coin" << endl;
				glPushMatrix();
				glTranslatef(0,0,-5);
				DrawObject(mg, CoinTexture.id);
				glPopMatrix();
			}
		}
		//rendering of catcher
		GameObject *catcher2 = (GameObject *)catcher;
		if (catcher2->active)
		{
			glPushMatrix();
			glTranslatef(0,0,-5);
			DrawObject(catcher2, CatcherTexture.id);
			glPopMatrix();
		}

		glPopMatrix();
	//}
}

void MiniGame::DrawMGBG()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glColor3f(0.5,0.5,0.5);
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