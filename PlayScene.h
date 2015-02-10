#pragma once
#include "tscene.h"
#include "TGlobal.h"
#include "BallSprite.h"
#include "BrickSprite.h"
#include "BulletSprite.h"
#include "CrystalSprite.h"
#include "ShipSprite.h"
#include "PaddleSprite.h"
#include "TSpriteString.h"
#include "BallCountString.h"
#include "BallCountDisplay.h"
#include "PowerUPSprite.h"
#include "TPlayers.h"
#include "ScoreString.h"
#include "misc.h"





#define STATE_START (1)
#define STATE_MAIN (2)
#define STATE_END (3)
#define STATE_NEWBALL (4)
#define STATE_NOBALL (5)
#define STATE_START2 (6)

class PlayScene :
	public TScene
{
public:

	PlayScene(void)
	{
		gongSound.setBuffer(TGlobal::resources.getSoundBuffer("gong2.wav"));
		setup();
	}


	virtual ~PlayScene(void)
	{

	}

	virtual void setup()
	{
		//displayList.add(TPlayers::pCrystalList);
		//displayList.add(TPlayers::pBulletList);
		//displayList.add(TPlayers::pExploList);
		displayList.add(TPlayers::pParticleList);
		//displayList.add(TPlayers::pShip);
		displayList.add(TPlayers::pPaddle);
		//displayList.add(TPlayers::pBall);
		displayList.add(TPlayers::pBallList);
		displayList.add(TPlayers::pBrickList);
		displayList.add(TPlayers::pScoreString);
		//displayList.add(TPlayers::pBallCountString);
		displayList.add(TPlayers::pBallCountDisplay);

		displayList.add(TPlayers::pPowerUpList);
		displayList.add(TPlayers::pDebugString);


		TScene::setup();


		//add text
		//TSpriteString * pss;
		//pss = new TSpriteString("persansb.ttf");
		//pss->setText(intToString(TPlayers::pBigBallList->size())+" Balls a Bouncing");
		//pss->setPosition(sf::Vector2f(20,20));
		//displayList.add(pss);
	}


	virtual void update(sf::Time elapsedTime)
	{
		stateTime=stateClock.getElapsedTime();

		switch(state)
		{
		case STATE_START:
			{
			if(firstTimeInState)
			{
				firstTimeInState=false;
				if(TGlobal::ballsLeft<5)TGlobal::ballsLeft+=2;


				for each (TSprite * pts in TPlayers::pPowerUpList->getVector())
				{
					PowerUpSprite * pBS = dynamic_cast<PowerUpSprite *>(pts);
					if(pBS)
					{
						pBS->changeState(POWERUPSTATE_INPLAY);
						pBS->isActive=false;
					}
				}
				for each (TSprite * pts in TPlayers::pBrickList->getVector())
				{
					BrickSprite * pBS = dynamic_cast<BrickSprite *>(pts);
					if(pBS)
					{
						pBS->changeState(BRICKSTATE_INITIAL);
						pBS->isActive=false;
					}
				}

				for(float iy=0;iy<10;iy++)
				{
					float pitch=0.8f+0.2f*iy;
					sf::Color color=TGlobal::randomBrightColor();
					for(float ix=0;ix<10;ix++)
					{
						BrickSprite * pActivateOne = (BrickSprite *) ( TPlayers::pBrickList->getPointerToNextInactive());
						pActivateOne->setScale(0.25f,0.25f);
						pActivateOne->setPosition(	(ix+0.5f)*(pActivateOne->getWidth()+7.0f),
													(iy+8.5f)*(pActivateOne->getHeight()+5.0f));
						pActivateOne->setScoreValue((int)(((11.0f-(float)iy)*10.0f)));
						pActivateOne->setPitch(pitch);
						pActivateOne->setColor(TGlobal::randomizeColor(color,10));
						pActivateOne->isActive=true;
					}
				}



				changeState(STATE_NEWBALL);

				//gongSound.setPitch(TGlobal::randomF(0.1f,1.9f));
				//gongSound.play();
				//for each (TGraphic * ptg in (TPlayers::pCrystalList->getVector()))
				//{
				//	CrystalSprite * pS = dynamic_cast<CrystalSprite *>(ptg);
				//	if(pS)
				//	{
				//		pS->isActive=false;
				//		pS->setOpacity(196);
				//	}
				//}
			}
			//float probSecFactor= 4.0f;
			//if(TGlobal::randomF()*probSecFactor   <   elapsedTime.asSeconds())
			//{
			//	CrystalSprite * pS = (CrystalSprite *) TPlayers::pCrystalList->getPointerToNextInactive();
			//	if(pS)
			//	{
			//		pS->setPosition(TGlobal::randomF(0.0f,(float)TGlobal::pMainWindow->getSize().x),-300.0f);
			//		pS->setSpeed(0.0f,TGlobal::randomF(100.0f,200.0f));
			//		pS->setEdgeBehaviour(TSprite::PREACTIVATE);
			//		pS->setScale(TGlobal::randomF(0.15f,0.5f));
			//		pS->setColor(TGlobal::randomBrightColor());
			//		pS->isActive=true;
			//	}
			//}
			//TPlayers::colisionCheck(TPlayers::pCrystalList,TPlayers::pBulletList);
			//if(stateTime.asSeconds()>=4.f)
			//{
			//	changeState(STATE_MAIN);
			//}
			}
			break;
		case STATE_START2:
			{
			if(firstTimeInState)
			{
				firstTimeInState=false;
				TGlobal::probabilityOfPowerUp*=1.5f;
				if(TGlobal::probabilityOfPowerUp>0.5f)TGlobal::probabilityOfPowerUp=0.5f;
				if(TGlobal::ballsLeft<5)TGlobal::ballsLeft+=2;

				for each (TSprite * pts in TPlayers::pPowerUpList->getVector())
				{
					PowerUpSprite * pBS = dynamic_cast<PowerUpSprite *>(pts);
					if(pBS)
					{
						pBS->changeState(POWERUPSTATE_INPLAY);
						pBS->isActive=false;
					}
				}
				for each (TSprite * pts in TPlayers::pBrickList->getVector())
				{
					BrickSprite * pBS = dynamic_cast<BrickSprite *>(pts);
					if(pBS)
					{
						pBS->changeState(BRICKSTATE_INITIAL);
						pBS->isActive=false;
					}
				}

				for(float iy=0;iy<20;iy++)
				{
					float pitch=0.8f+iy;
					sf::Color color=TGlobal::randomBrightColor();
					if(TGlobal::randomF()>0.5f)
					{
						for(float ix=0;ix<18;ix++)
						{
							BrickSprite * pActivateOne = (BrickSprite *) ( TPlayers::pBrickList->getPointerToNextInactive());
							if(pActivateOne)
							{
								pActivateOne->setScale(0.125f,0.125f);
								pActivateOne->setPosition(	(ix+0.75f)*(pActivateOne->getWidth()+7.0f),
															(iy+8.5f)*(pActivateOne->getHeight()+5.0f));
								pActivateOne->setScoreValue((int)((21.0f-(float)iy)*50.0f));
								pActivateOne->setPitch(pitch);
								pActivateOne->setColor(TGlobal::randomizeColor(color,20));
								pActivateOne->isActive=true;
								pActivateOne->changeState(BRICKSTATE_INITIAL);
							}
						}
					}
				}



				changeState(STATE_NEWBALL);

				//gongSound.setPitch(TGlobal::randomF(0.1f,1.9f));
				//gongSound.play();
				//for each (TGraphic * ptg in (TPlayers::pCrystalList->getVector()))
				//{
				//	CrystalSprite * pS = dynamic_cast<CrystalSprite *>(ptg);
				//	if(pS)
				//	{
				//		pS->isActive=false;
				//		pS->setOpacity(196);
				//	}
				//}
			}
			//float probSecFactor= 4.0f;
			//if(TGlobal::randomF()*probSecFactor   <   elapsedTime.asSeconds())
			//{
			//	CrystalSprite * pS = (CrystalSprite *) TPlayers::pCrystalList->getPointerToNextInactive();
			//	if(pS)
			//	{
			//		pS->setPosition(TGlobal::randomF(0.0f,(float)TGlobal::pMainWindow->getSize().x),-300.0f);
			//		pS->setSpeed(0.0f,TGlobal::randomF(100.0f,200.0f));
			//		pS->setEdgeBehaviour(TSprite::PREACTIVATE);
			//		pS->setScale(TGlobal::randomF(0.15f,0.5f));
			//		pS->setColor(TGlobal::randomBrightColor());
			//		pS->isActive=true;
			//	}
			//}
			//TPlayers::colisionCheck(TPlayers::pCrystalList,TPlayers::pBulletList);
			//if(stateTime.asSeconds()>=4.f)
			//{
			//	changeState(STATE_MAIN);
			//}
			}
			break;
		case STATE_NOBALL:
				if(TGlobal::ballsLeft<=0)
				{
					changeState(STATE_END);
				}
				else
				{
					if(stateTime.asSeconds()>3.0f)
					{
						
						changeState(STATE_NEWBALL);
					}
				}
			break;
		case STATE_NEWBALL:
			if(firstTimeInState)
			{
				for each (TSprite * pts in TPlayers::pBallList->getVector())
				{
					BallSprite * pBS = dynamic_cast<BallSprite *>(pts);
					if(pBS)
					{
						pBS->changeState(BALLSTATE_ONPADDLE);
						pBS->isActive=false;
					}
				}
				TGlobal::ballsLeft--;
				TSprite * pActivateOne = (TSprite *)(TPlayers::pBallList->getPointerToNextInactive());
				pActivateOne->isActive=true;
				int check = TPlayers::pBallList->getActiveCount();
				pActivateOne->setColor(sf::Color(255,255,255,255));
				pActivateOne->changeState(BALLSTATE_ONPADDLE);
				pActivateOne->setPosition(300,-500);
				((BallSprite * )pActivateOne)->pDebugStr->isActive=false;
				firstTimeInState=false;
				changeState(STATE_MAIN);
			}
			break;
		case STATE_MAIN:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			//if(stateTime.asSeconds()>=30.f)
			//{
			//	changeState(STATE_END);
			//}
			//TF may not be efficent
			if(TPlayers::pBallList->getActiveCount()==0)
			{
				changeState(STATE_NOBALL);
			}
			//TF may not be efficent
			if(TPlayers::pBrickList->getActiveCount()==0)
			{
				//bonusMultiplier+=1.0f;
				//TGlobal::score*=bonusMultiplier;
				changeState(STATE_START2);
			}
			break;
		case STATE_END:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			for each (TGraphic * ptg in (displayList.getVector()))
			{
				TSprite * pS = dynamic_cast<BallSprite *>(ptg);
				if(pS)
				{
					pS->setOpacity((int)(256.0f-stateTime.asSeconds()*64.0f));
				}
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeScene("TitleScene");
			}
			break;

		}


		TScene::update(elapsedTime);
		//if(sceneTime.asSeconds()>10.f) TGlobal::newSceneName="TitleScene";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) TGlobal::newSceneName="TitleScene";
	}

	virtual void startUp()
	{
		TScene::startUp();
		TGlobal::ballsLeft=3;
		TGlobal::score=0;
		changeState(STATE_START);
		bonusMultiplier=1.0f;
	}

protected:
	sf::Sound gongSound;
	float bonusMultiplier;
};

