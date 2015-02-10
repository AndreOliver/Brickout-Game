#pragma once
#include "powerupsprite.h"
class ShrinkPaddlePowerUpSprite :
	public PowerUpSprite
{
public:

	ShrinkPaddlePowerUpSprite(string textureFileName="explosion2.png")
	{
		setup();
		setColor(255,0,0,255);
	}
	
	virtual void applyPowerup()
	{
		TPlayers::pPaddle->changeState(PADDLESTATE_SMALL);
	}


	virtual ~ShrinkPaddlePowerUpSprite(void)
	{
	}
};

