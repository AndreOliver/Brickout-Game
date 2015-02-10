#pragma once
#include "TGraphicList.h"
#include "TSpriteString.h"
#include "TGlobal.h"
#include "TPlayers.h"
class TScene
{
public:


	TScene(void)
	{
	}

	virtual void setup()
	{
	}

	virtual void startUp()
	{
		sceneTime=sceneClock.restart();
	}

	virtual void update(sf::Time elapsedTime)
	{
		sceneTime=sceneClock.getElapsedTime();
		displayList.update(elapsedTime);
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))) 
		{
			TGlobal::pMainWindow->close();
			//exit(0);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::G))) 
		{
			TGlobal::godMode=true;
			TGlobal::probabilityOfPowerUp=1.0f;
			TPlayers::pDebugString->setText("god mode");
			//exit(0);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::H))) 
		{
			TGlobal::godMode=false;
			TPlayers::pDebugString->setText("");
			TGlobal::probabilityOfPowerUp=0.1f;
			//exit(0);
		}
	}

	virtual void draw(sf::RenderWindow & drawWindow)
	{
		displayList.draw(drawWindow);
	}


	virtual ~TScene(void)
	{
	}


	void changeState(int newState)
	{
		state=newState;
		stateTime=stateClock.restart();
		firstTimeInState=true;
	}

	void changeScene(string newScene)
	{
		TGlobal::newSceneName=newScene;
	}

protected:
	TGraphicList displayList;
	sf::Clock sceneClock;
	sf::Time sceneTime;


	sf::Clock stateClock;
	sf::Time stateTime;
	int state;
	bool firstTimeInState;
};

