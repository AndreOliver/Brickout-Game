#include "TGlobal.h"

	sf::RenderWindow * TGlobal::pMainWindow;
	sf::Time TGlobal::elapsedTime;
	TResources TGlobal::resources;
	string TGlobal::newSceneName="";
	int TGlobal::ballsLeft;
	int TGlobal::score=0;
	float TGlobal::probabilityOfPowerUp=0.1f;
	bool TGlobal::godMode=false;

