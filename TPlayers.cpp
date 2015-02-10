#include "TPlayers.h"
#include "TGraphicList.h"

#include "PaddleSprite.h"
#include "ShipSprite.h"
#include "BallSprite.h"
#include "BrickSprite.h"
#include "BulletSprite.h"
#include "CrystalSprite.h"
#include "ExploSprite.h"
#include "ParticleSprite.h"
#include "ScoreString.h"
#include "BallCountString.h"
#include "BallCountDisplay.h"
#include "PowerUpSprite.h"
#include "GrowPaddlePowerUpSprite.h"
#include "ShrinkPaddlePowerUpSprite.h"
#include "MultiBallPowerUpSprite.h"
#include "MultiBall2PowerUpSprite.h"
#include "SuperBallPowerUp.h"
#include "StickyPaddlePowerUp.h"
#include "LargeBallPowerUp.h"
#include "TSprite.h"
#include "TGlobal.h"

BallSprite * TPlayers::pBall;
PaddleSprite * TPlayers::pPaddle;
ShipSprite * TPlayers::pShip;
TGraphicList * TPlayers::pBallList;
TGraphicList * TPlayers::pBrickList;
TGraphicList * TPlayers::pBulletList;
TGraphicList * TPlayers::pCrystalList;
TGraphicList * TPlayers::pExploList;
TGraphicList * TPlayers::pParticleList;
ScoreString * TPlayers::pScoreString;
BallCountString * TPlayers::pBallCountString;
BallCountDisplay * TPlayers::pBallCountDisplay;
TGraphicList * TPlayers::pPowerUpList;
TSpriteString * TPlayers::pDebugString; 


void TPlayers::setup()
{
	TPlayers::pShip= new ShipSprite();
	TPlayers::pPaddle = new PaddleSprite();
	TPlayers::pBall = new BallSprite();

	int count;

	pBallList=new TGraphicList();
	//add balls
	count=200;
	for(int i=0;i<count;i++)
	{
		BallSprite * pSprite;
		pSprite=new BallSprite("ball02.png");
		pSprite->setPosition(sf::Vector2f(300,300));
		pBallList->add(pSprite);
	}

	pBrickList=new TGraphicList();
	//add bricks
	count=500;
	for(int i=0;i<count;i++)
	{
		BrickSprite * pSprite;
		pSprite=new BrickSprite();
		pSprite->setPosition(sf::Vector2f(300,300));
		pSprite->isActive=false;
		pBrickList->add(pSprite);
	}

	pBulletList=new TGraphicList();
	//add bullets
	count=64;
	for(int i=0;i<count;i++)
	{
		BulletSprite * pSprite;
		pSprite=new BulletSprite();
		pBulletList->add(pSprite);
	}

	pCrystalList=new TGraphicList();
	//add crystals
	count=64;
	for(int i=0;i<count;i++)
	{
		CrystalSprite * pSprite;
		pSprite=new CrystalSprite();
		pCrystalList->add(pSprite);
	}

	pExploList=new TGraphicList();
	//add explos
	count=32;
	for(int i=0;i<count;i++)
	{
		ExploSprite * pSprite;
		pSprite=new ExploSprite();
		pExploList->add(pSprite);
	}

	//******************************************************************
	pPowerUpList=new TGraphicList();
	//add powerups

	PowerUpSprite * pSprite;


	count=1;
	for(int i=0;i<count;i++)
	{
		pSprite=new GrowPaddlePowerUpSprite();
		pPowerUpList->add(pSprite);
	}

	count=1;
	for(int i=0;i<count;i++)
	{
		pSprite=new ShrinkPaddlePowerUpSprite();
		pPowerUpList->add(pSprite);
	}

	count=1;
	for(int i=0;i<count;i++)
	{
		pSprite=new MultiBall2PowerUpSprite();
		pPowerUpList->add(pSprite);
	}

	count=1;
	for(int i=0;i<count;i++)
	{
		pSprite=new MultiBallPowerUpSprite();
		pPowerUpList->add(pSprite);
	}

	count=30;
	for(int i=0;i<count;i++)
	{
		pSprite=new SuperBallPowerUp();
		pPowerUpList->add(pSprite);
	}

	count=30;
	for(int i=0;i<count;i++)
	{
		pSprite=new StickyPaddlePowerUp();
		pPowerUpList->add(pSprite);
	}

	count=30;
	for(int i=0;i<count;i++)
	{
		pSprite=new LargeBallPowerUp();
		pPowerUpList->add(pSprite);
	}


	//*******************************************************************
	pParticleList=new TGraphicList();
	//add particles
	count=1024;
	for(int i=0;i<count;i++)
	{
		ParticleSprite * pSprite;
		pSprite=new ParticleSprite();
		pParticleList->add(pSprite);
	}
	pScoreString = new ScoreString;
	pBallCountString=new BallCountString;
	pBallCountDisplay=new BallCountDisplay;
	pDebugString = new TSpriteString;
	pDebugString->setPosition(sf::Vector2f(0.0f,400.0f));
	pDebugString->isActive=true;
	pDebugString->setColor(sf::Color(255,255,255,128));
	pDebugString->setOpacity(255);
	pDebugString->setScale(0.5f);
	pDebugString->setSpeed(sf::Vector2f());
	pDebugString->setAcceleration(sf::Vector2f());
	
	pDebugString->setText("Test");
}


float TPlayers::distance(TSprite * pS1,TSprite * pS2)
{
	return TGlobal::getVectorSize(pS1->getPosition()-pS2->getPosition());
}




void TPlayers::colisionCheck(TGraphicList * pTGList1,TGraphicList * pTGList2)
{
	for(int i1=0;i1<pTGList1->size();i1++)
	{
		TSprite * pTS1 = (TSprite *) pTGList1->getPtrTGraphic(i1);
		if(pTS1->isActive)
		{
			for(int i2=0;i2<pTGList2->size();i2++)
			{
				TSprite * pTS2 = (TSprite *) pTGList2->getPtrTGraphic(i2);
				if(pTS2->isActive)
				{
					// both are active

					//float deltaX=fabsf(pTS1->getPositionX()-pTS2->getPositionX());
					//float deltaY=fabsf(pTS1->getPositionY()-pTS2->getPositionY());
					//float distance = sqrtf(deltaX*deltaX+deltaY*deltaY);
					if(distance(pTS1,pTS2)   <   (pTS1->getScaledCollisionCircleRadius()+pTS2->getScaledCollisionCircleRadius()))
					{
						// they have collided
						pTS1->hasCollidedWith(pTS2);
						pTS2->hasCollidedWith(pTS1);
					}
				}
			}
		}
	}
}




