#pragma once
#include "tscene.h"
#include "TGlobal.h"
#include "BallSprite.h"
#include "BulletSprite.h"
#include "ShipSprite.h"
#include "TSpriteString.h"
#include "TPlayers.h"
#include "misc.h"





#define STATE_START (1)
#define STATE_MAIN (2)
#define STATE_END (3)

class BallBounceScene :
	public TScene
{
public:

	BallBounceScene(void)
	{
		gongSound.setBuffer(TGlobal::resources.getSoundBuffer("gong2.wav"));
		setup();
	}


	virtual ~BallBounceScene(void)
	{

	}

	virtual void setup()
	{




		displayList.add(TPlayers::pBigBallList);
		displayList.add(TPlayers::pBulletList);
		displayList.add(TPlayers::pShip);
	

		//add text
		TSpriteString * pss;
		pss = new TSpriteString("persansb.ttf");
		pss->setText(intToString(TPlayers::pBigBallList->size())+" Balls a Bouncing");
		pss->setPosition(sf::Vector2f(20,20));
		displayList.add(pss);
	}


	virtual void update(sf::Time elapsedTime)
	{
		stateTime=stateClock.getElapsedTime();
		switch(state)
		{
		case STATE_START:
			if(firstTimeInState)
			{
				firstTimeInState=false;
				gongSound.setPitch(TGlobal::randomF(0.1f,1.9f));
				gongSound.play();
				for each (TGraphic * ptg in (displayList.getVector()))
				{
					TSprite * pS = dynamic_cast<BallSprite *>(ptg);
					if(pS)
					{
						pS->setPosition(sf::Vector2f(400.0f,400.0f));
						pS->setOpacity(0);
					}
				}
			}
			for each (TGraphic * ptg in (displayList.getVector()))
			{
				TSprite * pS = dynamic_cast<BallSprite *>(ptg);
				if(pS)
				{
					pS->setOpacity((int)(stateTime.asSeconds()*64.0f));
				}
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeState(STATE_MAIN);
			}
			break;
		case STATE_MAIN:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			if(stateTime.asSeconds()>=30.f)
			{
				changeState(STATE_END);
			}
			break;
		case STATE_END:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			for each (TGraphic * ptg in (displayList.getVector()))
			{
				TSprite * pS = dynamic_cast<BallSprite *>(ptg);
				if(pS)
				{
					pS->setOpacity((int)(256.0f-stateTime.asSeconds()*64.0f));
				}
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeScene("TitleScene");
			}
			break;

		}


		TScene::update(elapsedTime);
		//if(sceneTime.asSeconds()>10.f) TGlobal::newSceneName="TitleScene";
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) TGlobal::newSceneName="TitleScene";
	}

	virtual void startUp()
	{
		TScene::startUp();
		changeState(STATE_START);
	}

protected:
	sf::Sound gongSound;
};

