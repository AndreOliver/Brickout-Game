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
		setScale(0.3f);
		setRotationSpeed(TGlobal::randomF(-2000.0f,2000.0f));
		setSpecialness(0);
	}
	
	virtual void applyPowerup()
	{
		TPlayers::pPaddle->changeState(PADDLESTATE_SMALL);
	}

	virtual void update(sf::Time elapsed)
	{
		PowerUpSprite::update(elapsed);
	}


	virtual ~ShrinkPaddlePowerUpSprite(void)
	{
	}
};

