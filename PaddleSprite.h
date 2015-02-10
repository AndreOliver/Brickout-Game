#pragma once
#include "TGame.h"
#include "TSprite.h"
#include "TPlayers.h"
#include "BulletSprite.h"

#define PADDLESTATE_NORMAL 1
#define PADDLESTATE_LARGE  2
#define PADDLESTATE_SMALL  3


class PaddleSprite :
	public TSprite
{
public:

	PaddleSprite(string textureFileName=(string)"paddle001.png")
	{
		setTexture(TGlobal::resources.getTexture(textureFileName));
		setScale(0.5f);
		
		friction= 10.0f;
		edgeBehaviour=BOUNCE;
		setPosition(sf::Vector2f(TGlobal::pMainWindow->getSize().x/2.0f,TGlobal::pMainWindow->getSize().y*0.9f));
		hotGunTime=0.0f;
		startHotGunTime=0.1f;
		clangSoundPitch=TGlobal::randomF(0.25,3.0);
		TGlobal::pMainWindow->setMouseCursorVisible(false);
	}

	float getClangSoundPitch()
	{
		return clangSoundPitch;
	}


 	virtual void update(sf::Time elapsed)
	{
		switch(state)
		{
		case PADDLESTATE_NORMAL:
			if(firstTimeInState)
			{
				setScale(0.5f);
				firstTimeInState=false;
			}
			break;
		case PADDLESTATE_LARGE:
			if(firstTimeInState)
			{
				if(getScaleX()<1.5f) setScale(getScaleX()*1.2f);
				firstTimeInState=false;
			}
			if(timeInState>30.0f)
			{
				changeState(PADDLESTATE_NORMAL);
			}
			break;
		case PADDLESTATE_SMALL:
			if(firstTimeInState)
			{
			    setScale(0.25f);
				firstTimeInState=false;
			}
			if(timeInState>30.0f)
			{
				changeState(PADDLESTATE_NORMAL);
			}
			break;
		}
		float oldX = position.x;
		float newX = (float)(sf::Mouse::getPosition(* (TGlobal::pMainWindow)).x);
		speed.x=((newX-oldX)/elapsed.asSeconds())/10.0f;



		if(hotGunTime>0.0)
		{
			hotGunTime-=elapsed.asSeconds();
		}
		else
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				BulletSprite * pBS = (BulletSprite *) TPlayers::pBulletList->getPointerToNextInactive();
				if(pBS)
				{
					pBS->setPosition(position);
					pBS->isActive=true;
					float launchSpeed =600;
					pBS->setSpeedByAngle(rotation,launchSpeed);
					pBS->addSpeed(speed);
				}
				hotGunTime=startHotGunTime;
			}
			//multi-blast
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			{
				int count=10;
				float angle=rotation;
				float angleInc = 360.0f/count;
				float launchSpeed =400.0f;
				for(int i=0;i<count;i++)
				{
					BulletSprite * pBS = (BulletSprite *) TPlayers::pBulletList->getPointerToNextInactive();
					if(!pBS)break;
					pBS->setPosition(position);
					pBS->isActive=true;
					pBS->setSpeedByAngle(angle,launchSpeed);
					pBS->addSpeed(speed);

					angle+=angleInc;
				}
				hotGunTime=startHotGunTime*5.0f;
			}
		}


		TSprite::update(elapsed);
	}


	virtual ~PaddleSprite(void)
	{
	}

protected:

	float startHotGunTime;
	float hotGunTime;
	float clangSoundPitch;

};

