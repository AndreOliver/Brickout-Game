
#pragma once
#include "powerupsprite.h"
#include "BallSprite.h"
#include "TPlayers.h"

class MultiBallPowerUpSprite :
	public PowerUpSprite
{
public:

	MultiBallPowerUpSprite(string textureFileName="multiBall.png")
	{
		setup(textureFileName);
		setColor(TGlobal::randomizeColor(sf::Color(200,200,200,255)));
		setScale(0.2f);
		//setRotation(0.0f);
		setRotationSpeed(TGlobal::randomF(-2000.0f,2000.0f));
		setSpecialness(5);


	}
	
	virtual void applyPowerup()
	{
		int ballCount=(rand()%5)+1;
		if(TGlobal::randomF()>0.9)ballCount+=100;
		for(int i=0;i<ballCount;i++)
		{
			BallSprite * pNewBall = (BallSprite *)(TPlayers::pBallList->getPointerToNextInactive());
			if(pNewBall)
			{
				pNewBall->setPosition(TGlobal::randomF(0,(float)(TGlobal::pMainWindow->getSize().x)),-100.0f);
				pNewBall->setSpeed(TGlobal::randomF(-400.0f,400.0f),TGlobal::randomF(100.0f,200.0f));
				pNewBall->isActive=true;
				pNewBall->changeState(BALLSTATE_INPLAY);
			}
		}
	}

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}

	virtual ~MultiBallPowerUpSprite(void)
	{
	}
};


