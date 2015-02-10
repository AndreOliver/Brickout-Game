#include "BrickoutGame.h"


int WinMain()
{
	BrickoutGame game;

	game.setup("STML Proto Game",800,600,false);
	//game.setup("STML Proto Game",1080,720,true);
	//game.setup("STML Proto Game",800,600,true);
	//game.setup("STML Proto Game",1600,900,true);

	while (game.windowIsOpen())
    {
		//handle events
		game.eventHandler();
		//update
		game.update();
		//draw
		game.draw();
    }
    return 0;
}


