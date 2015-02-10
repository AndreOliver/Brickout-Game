
#pragma once
#include "powerupsprite.h"
#include "BallSprite.h"
#include "TPlayers.h"

class SuperBallPowerUp :
	public PowerUpSprite
{
public:

	SuperBallPowerUp(string textureFileName="multiBall.png")
	{
		setup(textureFileName);
		setColor(TGlobal::randomizeColor(sf::Color(255,255,0,255))); //gold
		setScale(0.2f);
		//setRotation(0.0f);
		setRotationSpeed(TGlobal::randomF(-2000.0f,2000.0f));
		setSpecialness(5);
	}
			

	virtual void applyPowerup()
	{
		for each  (TGraphic * pTG  in TPlayers::pBallList->getVector())
		{
			BallSprite * pCurBall = (BallSprite *) pTG;
			if(pCurBall->isActive)
			{
				pCurBall->setSpeed(pCurBall->getSpeed().x+TGlobal::randomF(-200,200),pCurBall->getSpeed().y+TGlobal::randomF(-200,200));
			}
		}
	}
	

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}

	virtual ~SuperBallPowerUp(void)
	{
	}
};


