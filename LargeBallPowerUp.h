#pragma once
#include "PowerUpSprite.h"


class LargeBallPowerUp :
	public PowerUpSprite
{
public:

	LargeBallPowerUp(string textureFileName="Ball02.png")
	{
		setup(textureFileName);
		setColor(0,255,0,255); //lime
		setScale(0.4f);
		setRotationSpeed(TGlobal::randomF(-2000.0f,2000.0f));
		setSpecialness(1);

	}
	
	virtual void applyPowerup()
	{
		
		for each  (TGraphic * pTG  in TPlayers::pBallList->getVector())
		{
			BallSprite * pCurBall = (BallSprite *) pTG;
			if(pCurBall->isActive)
			{
				pCurBall->setScale(0.75f);
			}
		}
	}

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}


	virtual ~LargeBallPowerUp(void)
	{
	}
};

