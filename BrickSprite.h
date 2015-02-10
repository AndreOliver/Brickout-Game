#pragma once
#include "TGame.h"
#include "TSprite.h"
#include "TPlayers.h"
#include "PowerUpSprite.h"

#define BRICKSTATE_INITIAL		0
#define BRICKSTATE_HIT_ONCE		1


class BrickSprite :
	public TSprite
{
public:

	BrickSprite(string textureFileName=(string)"paddle001.png")
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
		setScale(0.4f);
		baseSprite.setColor(sf::Color(0,0,255,255));
		friction= 10.0f;
		edgeBehaviour=BOUNCE;
		setPosition(sf::Vector2f(TGlobal::pMainWindow->getSize().x/2.0f,TGlobal::pMainWindow->getSize().y*0.2f));	
		clangSound.setBuffer(TGlobal::resources.getSoundBuffer("clang.wav"));
		clangSound.setLoop(false);
		clangSound.setPitch(TGlobal::randomF(0.25,3.0));
	}

	void setPitch(float f)
	{
		clangSound.setPitch(f);
	}

 	virtual void update(sf::Time elapsed)
	{
		switch(state)
		{
		case BRICKSTATE_INITIAL:
			if(firstTimeInState)
			{
				//setColor(sf::Color(128,128,128,255));
				firstTimeInState=false;
			}
			break;
		case BRICKSTATE_HIT_ONCE:
			if(firstTimeInState)
			{
				setColor(sf::Color(255,0,0,255));
				firstTimeInState=false;
			}
			break;
		}
		TSprite::update(elapsed);
	}

	virtual void hasCollidedWith(TSprite * pCollidedWith)
	{
		clangSound.play();
		switch(state)
		{
		case BRICKSTATE_INITIAL:
			changeState(BRICKSTATE_HIT_ONCE);
			break;
		case BRICKSTATE_HIT_ONCE:
			changeState(BRICKSTATE_INITIAL);
			isActive=false;
			TGlobal::score+=scoreValue;
			if(TGlobal::randomF()<=TGlobal::probabilityOfPowerUp)
			{
				PowerUpSprite * pPow = (PowerUpSprite *) (TPlayers::pPowerUpList->getPointerToRandInactive());
				if(pPow)
				{
					pPow->setPosition(position);
					pPow->isActive=true;
					pPow->changeState(POWERUPSTATE_INPLAY);
				}
			}
			break;
		}

	}



	virtual ~BrickSprite(void)
	{
	}


	int getScoreValue()
	{
		return scoreValue;
	}

	void setScoreValue(int n)
	{
		scoreValue=n;
	}


protected:

	sf::Sound clangSound;
	int scoreValue;

};

