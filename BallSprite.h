#pragma once
#include "TGame.h"
#include "TSprite.h"
#include "BrickSprite.h"
#include "PaddleSprite.h"
#include "TSpriteString.h"

#define BALLSTATE_INPLAY 1
#define BALLSTATE_DRAINING 2
#define BALLSTATE_ONPADDLE 3


class BallSprite :
	public TSprite
{
public:

	BallSprite(string textureFileName=(string)"Ball02.png")
	{
	    popSound.setBuffer(TGlobal::resources.getSoundBuffer("Balloon Popping.wav"));


		setTexture(TGlobal::resources.getTexture(textureFileName));
		//setColor(TGlobal::randomBrightColor());
		setScale(0.35f);
		setRotation(0.0f);
		setRotationSpeed(0.0f);
		setRotationAcceleration(0.0f);
		setGravity(0.0005f);
		changeState(BALLSTATE_ONPADDLE);

		pDebugStr = new TSpriteString("persansb.ttf");
		pDebugStr->setText("");
		pDebugStr->setColor(sf::Color(255,255,255));
		pDebugStr->setPosition(sf::Vector2f(200,200));
		pDebugStr->isActive=false;

		edgeBehaviour=BOUNCE_EXCEPT_BOTTOM;

	}


	virtual void draw(sf::RenderWindow & displayWin)
	{
		TSprite::draw(displayWin);
		if(pDebugStr->isActive) pDebugStr->draw(displayWin);
	}



	virtual void update(sf::Time elapsed)
	{
		//pDebugStr->setText("Debug");
		TSprite::update(elapsed);
		const float speedLimit=500.0f;
		if(speed.x>speedLimit)speed.x=speedLimit;
		if(speed.x<-speedLimit)speed.x=-speedLimit;
		if(speed.y>speedLimit)speed.y=speedLimit;
		if(speed.y<-speedLimit)speed.y=-speedLimit;
		switch(state)
		{
		case BALLSTATE_INPLAY:
			if(firstTimeInState)
			{
				//setPosition(TGlobal::randVector2f(0.f,(float)(TGlobal::pMainWindow->getSize().x),-200.f,-100.f));
				setAcceleration(sf::Vector2f(0.0f,0.0f));
				//set true for testing
				allwaysBounce=false;
				if(allwaysBounce)
				{
					edgeBehaviour=BOUNCE;
				}
				else
				{
					edgeBehaviour=BOUNCE_EXCEPT_BOTTOM;
				}
				firstTimeInState=false;
			}
			checkForCollisionsWithBricks();
			checkForCollisionWithPaddle();

			////collision with paddle
			//if(position.y+getHeight()/2.0  >= TPlayers::pPaddle->getPositionY() -TPlayers::pPaddle->getHeight()/2)     
			//{
			//	// used for testing so ball never drains
			//	allwaysBounce=true;
			//	if(allwaysBounce)
			//	{
			//		speed.y=fabsf(speed.y)*-1.f;
			//		speed.x+=(TPlayers::pPaddle->getSpeed().x)/2;
			//	}
			//	else
			//	{
			//		float min=TPlayers::pPaddle->getPositionX()-TPlayers::pPaddle->getWidth()/2 -getWidth()/2;
			//		float max=TPlayers::pPaddle->getPositionX()+TPlayers::pPaddle->getWidth()/2 +getWidth()/2;
			//		if(TGlobal::isBetween(getPositionX(),min,max))
			//		{
			//			speed.y=fabsf(speed.y)*-1.f;
			//			speed.x+=(TPlayers::pPaddle->getSpeed().x)/20;
			//			//clangSound.play();
			//		}
			//		else
			//		{
			//			changeState(BALLSTATE_DRAINING);
			//		}
			//	}
			//}
			break;
		case BALLSTATE_DRAINING:
			if(firstTimeInState)
			{
				edgeBehaviour=NONE;
				firstTimeInState=false;
			}
			if(timeInState>2.0f)
			{
				if(TPlayers::pBallList->getActiveCount()==1)
				{
					changeState(BALLSTATE_ONPADDLE);
				}
				else
				{
					isActive=false;
				}
			}
			break;
		case BALLSTATE_ONPADDLE:
			if(firstTimeInState)
			{
				edgeBehaviour=NONE;
				firstTimeInState=false;
			}
			position=TPlayers::pPaddle->getPosition();
			position.y-=TPlayers::pPaddle->getHeight()/2+getHeight()/2;
			//if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				setSpeed(sf::Vector2f(TPlayers::pPaddle->getSpeed().x,TGlobal::randomF(-300.0f,-180.0f)));
				changeState(BALLSTATE_INPLAY);
			}
			break;
		}
	}


	void checkForCollisionsWithBricks()
	{
		for each (TSprite * pSprite  in TPlayers::pBrickList->getVector())
		{
			BrickSprite * pBrick = (BrickSprite *) pSprite;

			if(pBrick->isActive) checkForCollisionWithBrick(pBrick);
		}
	}


	void checkForCollisionWithBrick(BrickSprite * pBrick)
	{
		const float paddleAccelerator = 1.02f;
		const float randBounceFactor = 10.0f;

		float brickLeft=pBrick->getPositionX() - pBrick->getWidth()/2.0f-(getWidth()/2);
		float brickRight=pBrick->getPositionX() + pBrick->getWidth()/2.0f+(getWidth()/2);
		float brickBottom=pBrick->getPositionY()+(pBrick->getHeight()/2.0f)+(getHeight()/2);
		float brickTop=pBrick->getPositionY()-(pBrick->getHeight()/2.0f)-(getHeight()/2);

		bool hasColided =false;


		if(TGlobal::isBetween(getPositionX(),brickLeft,brickRight))
		{
			
			if(getSpeed().y<0)
			{
				//ball going up
				if(getPositionY()>pBrick->getPositionY()+pBrick->getHeight()/2)
				{
					//ball is below paddle
					float delta =getPositionY()-brickBottom;

					if(delta<=0.0f)
					{
						// ball collision with bottom of paddle
						position.y-=delta;
						speed.y=fabsf(speed.y*paddleAccelerator)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
						//clangSound.setPitch(3.0f);
						//pBrick->hasCollidedWith(this);
						hasColided=true;
					}
				}
			}
			else
			{
				////ball going down
				if(getPositionY()<pBrick->getPositionY()-pBrick->getHeight()/2)
				{
					//ball is above paddle
					float delta =getPositionY()-brickTop;

					if(delta>=0.0f)
					{
						// ball collision with bottom of paddle
						position.y-=delta;
						speed.y=-fabsf(speed.y*paddleAccelerator)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
						//clangSound.setPitch(4.0f);
						//pBrick->hasCollidedWith(this);
						hasColided=true;
					}
				}
			}
		}

		if(TGlobal::isBetween(getPositionY(),brickTop,brickBottom))
		{


			if(getSpeed().x<0)
			{
				//ball going left
				if(getPositionX() > (pBrick->getPositionX()+(pBrick->getWidth()/2.0f))  )
				{
					//ball is on right of paddle
					float delta =getPositionX()-brickRight;

					if(delta<=0.0f)
					{
						// ball collision with right of paddle
						position.x-=delta;
						speed.x=fabsf(speed.x*paddleAccelerator)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
						//pBrick->hasCollidedWith(this);
						hasColided=true;

					}
				}
			}
			else
			{
				////ball going right
				if(getPositionX()<pBrick->getPositionX()-pBrick->getWidth()/2.0f)
				{
					//ball is on left of paddle
					float delta =getPositionX()-brickLeft;

					if(delta>=0.0f)
					{
						// ball collision with left of paddle
						position.x-=delta;
						speed.x=-fabsf(speed.x*paddleAccelerator)+TGlobal::randomF(-randBounceFactor,randBounceFactor);
						//pBrick->hasCollidedWith(this);
						hasColided=true;

					}
				}
			}
		}
		if(hasColided)pBrick->hasCollidedWith(this);
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
				}

			}
		}
	}




	virtual ~BallSprite(void)
	{
	}

	TSpriteString * pDebugStr;


protected:
	sf::Sound popSound;
	sf::Sound clangSound;
	bool allwaysBounce;
};

