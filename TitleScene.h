#pragma once
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>

#include "tscene.h"
#include "TGlobal.h"
#include "BallSprite.h"
#include "TSpriteString.h"
#include "misc.h"


#define TITLE_STATE_START (1)
#define TITLE_STATE_MAIN (2)
#define TITLE_STATE_FADE (3)
#define TITLE_STATE_END (4)



class TitleScene :
	public TScene
{
public:


	TitleScene(void)
	{
		setup();
	}

	virtual void setup()
	{
		//add balls
		int ballCount=2000;
		for(int i=0;i<ballCount;i++)
		{
			BallSprite * pBall;
			pBall=new BallSprite("ball02.png");
			pBall->setPosition(sf::Vector2f(300,300));
			displayList.add(pBall);
		}



		//add text
		TSpriteString * pss;
		pss = new TSpriteString("persansb.ttf");
		pss->setText("Brickout Game\nby Andre Oliver\nHomework 2\nPress Enter to Start");
		pss->setColor(sf::Color(0,0,255));
		pss->setPosition(sf::Vector2f(200,200));
		displayList.add(pss);

		changeState(TITLE_STATE_START);

		TScene::setup();
	}

	virtual void update(sf::Time elapsedTime)
	{
		stateTime=stateClock.getElapsedTime();
		switch(state)
		{
		case TITLE_STATE_START:
			if(firstTimeInState)
			{
				firstTimeInState=false;
				for each (TGraphic * ptg in (displayList.getVector()))
				{
					ptg->setOpacity(0);
				}
			}
			for each (TGraphic * ptg in (displayList.getVector()))
			{
				ptg->setOpacity(min(255,(int)(stateTime.asSeconds()*64.0f)));
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeState(TITLE_STATE_MAIN);
			}
			break;
		case TITLE_STATE_MAIN:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeState(TITLE_STATE_FADE);
			}
		case TITLE_STATE_FADE:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			for each (TGraphic * ptg in (displayList.getVector()))
			{
				ptg->setOpacity(max(0,(int)(256.0f-stateTime.asSeconds()*64.0f)));
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeState(TITLE_STATE_END);
			}
			break;
		case TITLE_STATE_END:
			if(firstTimeInState)
			{
				firstTimeInState=false;
			}
			if(stateTime.asSeconds()>=4.f)
			{
				changeState(TITLE_STATE_START);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) changeScene("PlayScene");
		TScene::update(elapsedTime);
	}



	virtual void startUp()
	{
		TScene::startUp();
		changeState(TITLE_STATE_START);
	}




	virtual ~TitleScene(void)
	{
	}
};

