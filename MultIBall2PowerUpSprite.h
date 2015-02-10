
#pragma once
#include "powerupsprite.h"
#include "BallSprite.h"
#include "TPlayers.h"

class MultiBall2PowerUpSprite :
	public PowerUpSprite
{
public:

	MultiBall2PowerUpSprite(string textureFileName="multiBall.png")
	{
		setup(textureFileName);
		setColor(sf::Color(0,0,255,255));
		setScale(0.2f);
		//setRotation(0.0f);
		setRotationSpeed(TGlobal::randomF(-2000.0f,2000.0f));
		setSpecialness(3);


	}
	
	virtual void applyPowerup()
	{
		vector<BallSprite *> vNewBalls;
		int count=0;
		int activateCount=0;
		int activateCount2=0;
		for each  (TGraphic * pTG  in TPlayers::pBallList->getVector())
		{
			BallSprite * pCurBall = (BallSprite *) pTG;
			if(pCurBall->isActive)
			{
				count++;
				if(count>5)break;
				BallSprite * pNewBall = (BallSprite *) TPlayers::pBallList->getPointerToNextInactive();
				if(pNewBall)
				{
					activateCount++;
					pNewBall->setPosition(pCurBall->getPosition());
					pNewBall->setSpeed(pCurBall->getSpeed().x+TGlobal::randomF(-200,200),pCurBall->getSpeed().y+TGlobal::randomF(-200,200));
					pNewBall->changeState(BALLSTATE_INPLAY);
					vNewBalls.push_back(pNewBall);
				}
			}
		}

		for each (BallSprite * pBS in vNewBalls)
		{
			activateCount2++;
			pBS->isActive=true;
		}
		TPlayers::pDebugString->setText(std::to_string(count)+"  "+std::to_string(activateCount)+"  "+std::to_string(activateCount2));
	}

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}

	virtual ~MultiBall2PowerUpSprite(void)
	{
	}
};


