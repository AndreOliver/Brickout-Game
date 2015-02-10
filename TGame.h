#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TGraphicList.h"
#include "TResources.h"
#include "TGraphic.h"
#include "stdlib.h"
#include "TGlobal.h"
#include "TScene.h"


class TGame
{
public:

	TGame(void)
	{
		srand((unsigned int)time(NULL));
	}

	virtual void setup(string gameName,int gameWidth, int gameHeight, bool fullScreen =false)
	{
		if(fullScreen)
		{
			TGlobal::pMainWindow = new sf::RenderWindow(sf::VideoMode(gameWidth, gameHeight), gameName, sf::Style::Fullscreen);
		}
		else
		{
			TGlobal::pMainWindow = new sf::RenderWindow(sf::VideoMode(gameWidth, gameHeight), gameName);
		}
		TGlobal::pMainWindow->setVerticalSyncEnabled(true);
		TGlobal::elapsedTime=gameClock.restart();
	}




	virtual void update()
	{
		checkForNewScene();
		TGlobal::elapsedTime=gameClock.restart();
		currentScene->update(TGlobal::elapsedTime);
	}



	void checkForNewScene()
	{
		if(TGlobal::newSceneName!="")
		{
			if(mapTScene.find(TGlobal::newSceneName)!=mapTScene.end())
			{
				currentScene=mapTScene[TGlobal::newSceneName];
				currentScene->startUp();
				TGlobal::newSceneName="";
			}
			else
			{
				throw (string)"Error: Invalid Scene Name in TGame.h.";
			}
		}
	}



	virtual void draw()
	{
		TGlobal::pMainWindow->clear();

		currentScene->draw(*TGlobal::pMainWindow);

		TGlobal::pMainWindow->display();
	}


	void eventHandler()
	{
		sf::Event event;
		while (TGlobal::pMainWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				TGlobal::pMainWindow->close();
		}
	}

	bool windowIsOpen()
	{
		return TGlobal::pMainWindow->isOpen();
	}

	virtual ~TGame(void)
	{
	}

protected:
	sf::Clock gameClock;
	map<string,TScene *> mapTScene;
	TScene * currentScene;
};

