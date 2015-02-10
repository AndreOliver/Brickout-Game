#pragma once
#include "PowerUpSprite.h"


class StickyPaddlePowerUp :
	public PowerUpSprite
{
public:

	StickyPaddlePowerUp(string textureFileName="Ball02.png")
	{
		setup(textureFileName);
		setColor(0,255,255,255); //cyan
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
				
				pCurBall->changeState(BALLSTATE_ONPADDLE);
			}
		}

		
	}

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}


	virtual ~StickyPaddlePowerUp(void)
	{
	}
};

