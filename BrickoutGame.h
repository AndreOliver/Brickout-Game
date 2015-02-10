#pragma once
#include "tgame.h"
#include "TPlayers.h"
#include "PlayScene.h"
#include "TitleScene.h"

class BrickoutGame :
	public TGame
{
public:

	BrickoutGame(void)
	{
	}

	virtual void setup(string gameName,int gameWidth, int gameHeight, bool fullScreen=false )
	{
		TGame::setup(gameName, gameWidth, gameHeight, fullScreen);

		TPlayers::setup();
		
		// Set up all the Scenes
		//-----------------------------------------------------------
		PlayScene * pBBScene = new PlayScene;
		mapTScene["PlayScene"]=pBBScene;

		TitleScene * pTitleScene = new TitleScene;
		mapTScene["TitleScene"]=pTitleScene;

		// Select the Starting Scene
		//-----------------------------------------------------------
		TGlobal::newSceneName="TitleScene";
	}


	virtual ~BrickoutGame(void)
	{
	}
};

