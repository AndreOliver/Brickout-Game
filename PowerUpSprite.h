
#pragma once
#include "TGame.h"
#include "TSprite.h"
#include "BrickSprite.h"
#include "PaddleSprite.h"
#include "TSpriteString.h"
#include "ParticleSprite.h"

#define POWERUPSTATE_INPLAY 1
#define POWERUPSTATE_DRAINING 2


class PowerUpSprite :
	public TSprite
{
public:

	PowerUpSprite()
	{
		setup();
	}

	PowerUpSprite(string textureFileName)
	{
		setup(textureFileName);
	}

	virtual void setup(string textureFileName="explosion2.png")
	{
	    popSound.setBuffer(TGlobal::resources.getSoundBuffer("Balloon Popping.wav"));
		specialness=0;

		setTexture(TGlobal::resources.getTexture(textureFileName));
		setColor(TGlobal::randomBrightColor());
		setScale(0.4f);
		setRotation(0.0f);
		setRotationSpeed(0.0f);
		setRotationAcceleration(0.0f);

		edgeBehaviour= INACTIVATE;
	}

	virtual void update(sf::Time elapsed)
	{
		if(isActive)
		{
			//pDebugStr->setText("Debug");
			TSprite::update(elapsed);
			float speedLimit=500;
			if(speed.x>speedLimit)speed.x=speedLimit;
			if(speed.x<-speedLimit)speed.x=-speedLimit;
			if(speed.y>speedLimit)speed.y=speedLimit;
			if(speed.y<-speedLimit)speed.y=-speedLimit;
			switch(state)
			{
			case POWERUPSTATE_INPLAY:
				if(firstTimeInState)
				{
					setSpeed(sf::Vector2f(0.0f,300.0f));
					setAcceleration(sf::Vector2f(0.0f,0.0f));
					firstTimeInState=false;
				}
				for(int i=0;i<specialness;i++)
				{
					ParticleSprite * pPart = (ParticleSprite *)(TPlayers::pParticleList->getPointerToNextInactive());
					if(pPart)
					{
						pPart->setPosition(position);
						const float setSpeed=300.0f;
						pPart->setSpeed(TGlobal::randomF(-setSpeed,setSpeed),TGlobal::randomF(-setSpeed,setSpeed));
						pPart->isActive=true;
						pPart->setScale(1.0f);
						pPart->setFriction(0.0f);
						pPart->setDuration(0.1f*(float)specialness);
						if(TGlobal::randomF()<0.5f)
						{
							pPart->setColor(TGlobal::randomizeColor(getColor()));
						}
						else
						{
							pPart->setColor(255,255,255,255);
						}
						pPart->changeState(PARTICLE_STATE_START);
					}
				}
				checkForCollisionWithPaddle();

				break;
			case POWERUPSTATE_DRAINING:
				if(firstTimeInState)
				{
					edgeBehaviour=NONE;
					firstTimeInState=false;
				}
				if(timeInState>2.0f)
				{
					isActive=false;
				}
				break;
			}
		}
	}



	void checkForCollisionWithPaddle()
	{
		PaddleSprite * pPaddle = TPlayers::pPaddle;
		const float randBounceFactor = 10.0f;
		//bool inVerticalChanel = TGlobal::isBetween(	getPositionX(),
		//						pPaddle->getPositionX()-(pPaddle->getWidth()/2.0f)-(getWidth()/2.0f),
		//						pPaddle->getPositionX()+(pPaddle->getWidth()/2.0f)+(getWidth()/2.0f) );
		//bool inHorizantalChannel = TGlobal::isBetween(	getPositionY(),
		//						pPaddle->getPositionY()-(pPaddle->getHeight()/2.0f)-(getHeight()/2.0f),
		//						pPaddle->getPositionY()+(pPaddle->getHeight()/2.0f)+(getHeight()/2.0f) );
		bool inVerticalChanel = TGlobal::isBetween(	getPositionX(),
								pPaddle->getPositionX()-(pPaddle->getWidth()/2.0f),
								pPaddle->getPositionX()+(pPaddle->getWidth()/2.0f));
		bool inHorizantalChannel = TGlobal::isBetween(	getPositionY(),
								pPaddle->getPositionY()-(pPaddle->getHeight()/2.0f),
								pPaddle->getPositionY()+(pPaddle->getHeight()/2.0f));
		if(inVerticalChanel)
		{			
			if(getPositionY()<pPaddle->getPositionY())
			{
				//ball center is above paddle center
				float delta = fabsf(getPositionY()-pPaddle->getPositionY()) - ((getHeight()+pPaddle->getHeight())/2.0f);
				//if delta is zero or less we have collision
				if(delta<0.0f)
				{
					// ball collision with top of paddle
					//pPaddle->setColor(TGlobal::randomBrightColor());
					position.y+=delta;
					speed.y=-fabsf(speed.y)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
					speed.x+=(pPaddle->getSpeed().x)/4.0f;
					clangSound.setPitch(pPaddle->getClangSoundPitch());
					clangSound.play();
					applyPowerup();
					isActive=false;
				}
			}
			else
			{
				//ball center is at or below paddle Center
				float delta = fabsf(getPositionY()-pPaddle->getPositionY()) - ((getHeight()+pPaddle->getHeight())/2.0f);
				//if delta is zero or less we have collision
				if(delta<0.0f)
				{
					// ball collision with bottom of paddle
					//pPaddle->setColor(TGlobal::randomBrightColor());
					position.y-=delta;
					speed.y=fabsf(speed.y)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
					clangSound.setPitch(pPaddle->getClangSoundPitch());
					clangSound.play();
					applyPowerup();
					isActive=false;
				}

			}
		}

		if(inHorizantalChannel)
		{			
			if(getPositionX()<pPaddle->getPositionX())
			{
				//ball center is left of paddle center
				float delta = fabsf(getPositionX()-pPaddle->getPositionX()) - ((getWidth()+pPaddle->getWidth())/2.0f);
				//if delta is zero or less we have collision
				if(delta<0.0f)
				{
					// ball collision with left of paddle
					//pPaddle->setColor(TGlobal::randomBrightColor());
					position.x+=delta;
					speed.x=-fabsf(speed.x)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
					clangSound.setPitch(pPaddle->getClangSoundPitch());
					clangSound.play();
					applyPowerup();
					isActive=false;
				}
			}
			else
			{
				//ball center is at right of paddle Center
				float delta = fabsf(getPositionX()-pPaddle->getPositionX()) - ((getWidth()+pPaddle->getWidth())/2.0f);
				//if delta is zero or less we have collision
				if(delta<0.0f)
				{
					// ball collision with bottom of paddle
					//pPaddle->setColor(TGlobal::randomBrightColor());
					position.x-=delta;
					speed.x=fabsf(speed.x)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
					clangSound.setPitch(pPaddle->getClangSoundPitch());
					clangSound.play();
					applyPowerup();
					isActive=false;
				}

			}
		}
	}

	virtual void applyPowerup()=0;

	virtual ~PowerUpSprite(void)
	{
	}

	void setSpecialness(int i)
	{
		specialness=i;
	}

protected:
	sf::Sound popSound;
	sf::Sound clangSound;
	int specialness;
};

